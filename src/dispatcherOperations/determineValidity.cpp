//
// Created by AKazmirchuk on 13.11.2025.
//



#include "DispatcherOperations.h"



const ErrorLevel DispatcherOperations::getErrorLevelFrom(const std::string& functionName)
{
    //Соответствие имени вызывающей функции и уровня логирования
    const std::map<std::string, ErrorLevel> matchingFunctionNameAndErrorLevel{
            {"ConverterJSON::ConfigConverterJSON::initialize",              ErrorLevel::fatal},
            {"ConverterJSON::checkFilePath",                                ErrorLevel::fatal},
            {"ConverterJSON::checkRequests",                                ErrorLevel::fatal},
            {"DispatcherOperations::readTextFileFromMultipleFiles",         ErrorLevel::error},
            {"SearchEngine::readDocsFromFiles",                             ErrorLevel::fatal},
            {"SearchEngine::readDocsFromFilesRef",                          ErrorLevel::fatal},
            {"SearchEngine::writeAnswersToFile",                            ErrorLevel::fatal}
    };

    //Вернуть уровень логирования
    return matchingFunctionNameAndErrorLevel.at(functionName);
}

ErrorLevel DispatcherOperations::getErrorLevel(const std::string& callingFunctionStr)
{
    //Подготовить переменные для определения начала и конца имени функции
    std::string::size_type endNameFunction{callingFunctionStr.find('(') - 1};
    std::string::size_type beginNameFunction{endNameFunction};
    //Количество символов имени функции
    std::string::size_type symbolsNumber{};

    //Подсчитать количествоо символов имени функции
    for (; callingFunctionStr[beginNameFunction] != ' '; --beginNameFunction, ++symbolsNumber)
    {}

    //Вернуть уровень логирования
    return getErrorLevelFrom(callingFunctionStr.substr(beginNameFunction + 1, symbolsNumber));
}

void DispatcherOperations::determineValidity(
        const std::string &filePath,
        ErrorCode errorCode,
        ErrorLevel errorLevel,
        const std::string &message,
        const boost::source_location &callingFunction)
{
    //Преобразовать объект предоставленный BOOST_CURRENT_LOCATION в строку
    std::string callingFunctionStr{callingFunction.to_string()};

    //Если уровень логирования не указан
    if (errorLevel == ErrorLevel::no_level)
    {
        //Определить уровень логирования по имени функции
        errorLevel = getErrorLevel(callingFunctionStr);
    }

    //Окончательное сообщение для логирования
    std::string completedMessage;

    //Если путь файла указан
    if (!filePath.empty())
    {
        //Подготовить окончательное сообщение для логирования
        completedMessage = descriptionErrorCode.at(errorCode) + ": " + filePath + ". " +
                           static_cast<std::string>("Calling function: ") + callingFunctionStr + ". " + message;
    }
    else
    {
        std::cout << '\n' << "filePath: " << filePath << '\n';
        //Подготовить окончательное сообщение для логирования
        completedMessage = descriptionErrorCode.at(errorCode) + ". " +
                           static_cast<std::string>("Calling function: ") + callingFunctionStr + ". " + message;
    }

    //Если при операции с файлом или JSON-объектом произошла ошибка
    if (errorCode != ErrorCode::no_error)
    {
        //Записать в лог по уровню логирования
        switch (errorLevel)
        {
            case ErrorLevel::fatal:
                kav::Logger::fatal(completedMessage);
                //Выбросить исключение
                throw OperationException(completedMessage);
            case ErrorLevel::error:
                kav::Logger::error(completedMessage);
                return;
            case ErrorLevel::warning:
                kav::Logger::warning(completedMessage);
                return;
            case ErrorLevel::info:
                kav::Logger::info(completedMessage);
                return;
            case ErrorLevel::debug:
                kav::Logger::debug(completedMessage);
                return;
        }
    }
}