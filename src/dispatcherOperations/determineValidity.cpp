//
// Created by AKazmirchuk on 13.11.2025.
//



#include "DispatcherOperations.h"



ErrorLevel DispatcherOperations::getErrorLevelFrom(const std::string& functionName)
{
    //Вернуть уровень логирования
    return matchingFunctionNameAndErrorLevel.at(functionName);
}

void DispatcherOperations::setErrorLevelFrom(const std::map<std::string, ErrorLevel>& in_matchingFunctionNameAndErrorLevel)
{
    //Добавить соответствия для внутреннего использования//TODO На тест, рассмотреть возможность изменения уровня логирования для закрытых функций в зависимости от уровня логирования вызываемых открытых
    matchingFunctionNameAndErrorLevel["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::error;

    //Для каждого соответствия
    for (auto& elem : in_matchingFunctionNameAndErrorLevel)
    {
        //Добавить пару записей
        matchingFunctionNameAndErrorLevel.insert(elem);
    }

}

unsigned int DispatcherOperations::getNumberOfThreads()
{
    return numberOfThreads;
}


std::string DispatcherOperations::getFunctionName(const boost::source_location &callingFunction)
{
    //Преобразовать объект предоставленный BOOST_CURRENT_LOCATION в строку
    std::string callingFunctionStr{callingFunction.to_string()};

    //Подготовить переменные для определения начала и конца имени функции
    std::string::size_type endNameFunction{callingFunctionStr.find('(') - 1};
    std::string::size_type beginNameFunction{endNameFunction};
    //Количество символов имени функции
    std::string::size_type symbolsNumber{};

    //Подсчитать количество символов имени функции
    for (; callingFunctionStr[beginNameFunction] != ' '; --beginNameFunction, ++symbolsNumber)
    {}

    return callingFunctionStr.substr(beginNameFunction + 1, symbolsNumber);
}

ErrorLevel DispatcherOperations::getErrorLevel(const boost::source_location &callingFunction)
{
    //Вернуть уровень логирования
    return getErrorLevelFrom(getFunctionName(callingFunction));
}
//TODO На тест, проверить при ошибке вызова простой функции какая  функция указана
void DispatcherOperations::determineValidity(
        const std::string &filePath,
        ErrorCode errorCode,
        ErrorLevel errorLevel,
        const std::string& message,
        const boost::source_location &callingFunction)
{
    //Преобразовать объект предоставленный BOOST_CURRENT_LOCATION в строку
    std::string callingFunctionStr{callingFunction.to_string()};

    //Если уровень логирования не указан
    if (errorLevel == ErrorLevel::no_level)
    {
        //Определить уровень логирования по имени функции
        errorLevel = getErrorLevel(callingFunction);
    }

    //Окончательное сообщение для логирования
    std::string completedMessage;

    //Если путь файла указан
    if (!filePath.empty())
    {
        //Подготовить окончательное сообщение для логирования
        completedMessage = DescriptionErrorCode::descriptionErrorCode(errorCode) + ": " + filePath + ". " +
                           static_cast<std::string>("Calling function: ") + callingFunctionStr + ". " + message;
    }
    else
    {
        //Подготовить окончательное сообщение для логирования
        completedMessage = DescriptionErrorCode::descriptionErrorCode(errorCode) + ". " +
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
            case ErrorLevel::no_level:
                break;//TODO На тест, проверить этот случай
        }
    }
}