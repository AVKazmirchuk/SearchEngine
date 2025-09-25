//
// Created by Alexander on 13.06.2025.
//

#ifndef SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H
#define SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H



#include "kav/operationFileAndJSON.h"
#include "kav/logger.h"
#include "types.h"



/**
 * Уровни логирования
 */
enum class ErrorLevel
{
    no_level,
    debug,
    info,
    warning,
    error,
    fatal
};

/**
 * Коды ошибок работы с файлами
 */
enum class ErrorCode
{
    no_error,
    error_file_missing,
    error_file_not_open_read,
    error_file_not_read,
    error_file_not_open_write,
    error_file_not_write,
    error_json_structure_corrupted,
    error_json_structure_not_match,
    error_array_empty,
    error_file_paths_array_empty,
    error_requests_array_empty,
    error_all_files_not_read
};

/**
 * Описание кодов ошибок
 */
static const std::map<ErrorCode, std::string> descriptionErrorCode{

        {ErrorCode::no_error,                       ""},
        {ErrorCode::error_file_missing,             "This file is missing:"},
        {ErrorCode::error_file_not_open_read,       "This file cannot be opened for reading:"},
        {ErrorCode::error_file_not_read,            "This file has not been read:"},
        {ErrorCode::error_file_not_open_write,      "This file cannot be opened for writing:"},
        {ErrorCode::error_file_not_write,           "This file has not been write:"},
        {ErrorCode::error_json_structure_corrupted, "The structure of this file is corrupted:"},
        {ErrorCode::error_json_structure_not_match, "The structure of this file does not match the required one:"},
        {ErrorCode::error_array_empty,              "The array is empty"},
        {ErrorCode::error_file_paths_array_empty,   "The array paths of this file is empty:"},
        {ErrorCode::error_requests_array_empty,     "The array requests of this file is empt:"},
        {ErrorCode::error_all_files_not_read,       "All files have not been read"}

};

/**
 * Класс реализует исключение
 */
class OperationException : public std::exception
{

public:

    /**
     * Инициализирует код исключения
     * @param in_errorCode Код ошибки
     * @param in_information Ссылка на информацию по ошибке
     */
    explicit OperationException(ErrorCode in_errorCode, const std::string &in_information = "") : errorCode(
            in_errorCode)
    {
        information = descriptionErrorCode.at(errorCode) + ": " + in_information + '.';
    }

    /**
     * Получить информацию по исключению
     * @return Информация по исключению
     */
    [[nodiscard]] const char *what() const noexcept override
    {
        return information.c_str();
    }

    /**
     * Получить код исключения
     * @return Код исключения
     */
    [[nodiscard]] ErrorCode getErrorCode() const
    {
        //Вернуть код ошибки
        return errorCode;
    }

private:

    //Код ошибки
    ErrorCode errorCode;
    //Информация по ошибке
    std::string information;

};


/**
 * Класс диспетчер операций c файлами и JSON-объектами
 * Выполняет операции с файлами (чтение-запись), проверку JSON-объекта и при необходимости определяет уровень логирования,
 * и логирует события, по имени вызывающей функции при ошибке операции.
 */
class DispatcherOperationValidity
{

public:

    /**
      * Записать JSON-файл
      * @param filePath Ссылка на путь JSON-файла
      * @param objectJSON Ссылка на JSON-объект для записи
      * @param formatByWidth Ширина отступа
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const int formatByWidth = 2,
                                   ErrorLevel errorLevel = ErrorLevel::no_level, const std::string &message = "",
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Проверить JSON-структуру на соответствие шаблону
      * @param filePath Ссылка на путь JSON-файла
      * @param objectJSON Ссылка на JSON-объект для проверки
      * @param objectJSONTemplate Ссылка на JSON-объект шаблона
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode
    checkJSONStructureMatch(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                            ErrorLevel errorLevel = ErrorLevel::no_level, const std::string &message = "",
                            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Проверить массив JSON-объекта путей файлов на пустоту
      * @param objectJSON Ссылка на JSON-объект для проверки
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode checkFilePathsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::no_level,
                                         const std::string &message = "",
                                         const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Проверить массив JSON-объекта запросов на пустоту
      * @param objectJSON Ссылка на JSON-объект для проверки
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode checkRequestsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::no_level,
                                        const std::string &message = "",
                                        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать JSON-файл
      * @param filePath Ссылка на путь JSON-файла
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара JSON-объекта и кода ошибки
      */
    static std::pair<JSON, ErrorCode>
    readJSONFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::no_level,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать текстовый файл
      * @param filePath Ссылка на путь текстового файла
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара текста и кода ошибки
      */
    static std::pair<std::string, ErrorCode>
    readTextFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::no_level,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать несколько текстовых файлов одновременно в разных потоках
      * @param filePaths Ссылка на путь контейнера путей файлов
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара контейнер текстов и кода ошибки
      */
    static std::pair<std::vector<std::string>, ErrorCode> readMultipleTextFiles(const std::vector<std::string>& filePaths, ErrorLevel errorLevel = ErrorLevel::no_level,
                                                                                    const std::string &message = "",
                                                                                    const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

private:

    /**
     * Преобразовать код ошибки из внешней функции во внутренний код ошибки
     * @param errorCode Код ошибки из внешней функции
     * @return Код ошибки внутренний
     */
    static const ErrorCode convertErrorCodeFrom(const kav::ErrorCode errorCode)
    {
        //Соответствие кодов ошибки внутреннего и внешнего
        const std::map<kav::ErrorCode, ErrorCode> matchingErrorCodes{

                {kav::ErrorCode::no_error,                       ErrorCode::no_error},
                {kav::ErrorCode::error_file_missing,             ErrorCode::error_file_missing},
                {kav::ErrorCode::error_file_not_open_read,       ErrorCode::error_file_not_open_read},
                {kav::ErrorCode::error_file_not_read,            ErrorCode::error_file_not_read},
                {kav::ErrorCode::error_file_not_open_write,      ErrorCode::error_file_not_open_write},
                {kav::ErrorCode::error_file_not_write,           ErrorCode::error_file_not_write},
                {kav::ErrorCode::error_json_structure_corrupted, ErrorCode::error_json_structure_corrupted},
                {kav::ErrorCode::error_json_structure_not_match, ErrorCode::error_json_structure_not_match},
                {kav::ErrorCode::error_array_empty,              ErrorCode::error_array_empty}

        };

        //Вернуть внутренний код ошибки
        return matchingErrorCodes.at(errorCode);

    }

    /**
     * Получить уровень логирования на основе вызывающей функции
     * @param functionName Ссылка на имя функции
     * @return Уровень логировани
     */
    static const ErrorLevel getErrorLevelFrom(const std::string& functionName)
    {
        //Соответствие имени вызывающей функции и уровня логирования
        const std::map<std::string, ErrorLevel> matchingFunctionNameAndErrorLevel{
                {"ConverterJSON::ConfigConverterJSON::initialize",     ErrorLevel::fatal},
                {"ConverterJSON::checkFilePath",                       ErrorLevel::fatal},
                {"ConverterJSON::checkRequests",                       ErrorLevel::fatal},
                {"DispatcherDetermineValidity::readMultipleTextFiles", ErrorLevel::error},
                {"SearchEngine::readDocsFromFiles",                    ErrorLevel::fatal},
                {"SearchEngine::writeAnswersToFile",                   ErrorLevel::fatal}
        };

        //Вернуть уровень логирования
        return matchingFunctionNameAndErrorLevel.at(functionName);
    }

    /**
     * Получить уровень логирования из объекта предоставленного BOOST_CURRENT_LOCATION
     * @param callingFunctionStr Ссылка на объект предоставленный BOOST_CURRENT_LOCATION
     * @return Уровень логирования
     */
    static ErrorLevel getFunctionName(const std::string& callingFunctionStr)
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

    /**
     * Логировать событие по коду ошибки и уровню логирования
     * @param filePath Ссылка на путь к файлу
     * @param errorCode Код ошибки
     * @param errorLevel Уровень логирования
     * @param message Ссылка на сообщение
     * @param callingFunction Ссылка на вызывающую функцию
     */
    static void determineValidity(const std::string &filePath, ErrorCode errorCode = ErrorCode::no_error,
                                  ErrorLevel errorLevel = ErrorLevel::no_level,
                                  const std::string &message = "",
                                  const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION)
    {
        //Преобразовать объект предоставленный BOOST_CURRENT_LOCATION в строку
        std::string callingFunctionStr{callingFunction.to_string()};

        //Если уровень логирования не указан
        if (errorLevel == ErrorLevel::no_level)
        {
            //Определить уровень логирования по имени функции
            errorLevel = getFunctionName(callingFunctionStr);
        }

        //Подготовить окончательное сообщение для логирования
        std::string completedMessage{descriptionErrorCode.at(errorCode) + ": " + filePath + ". " +
                                     static_cast<std::string>("Calling function: ") + callingFunctionStr + ". " + message};

        //Если при операции с файлом или JSON-объектом произошла ошибка
        if (errorCode != ErrorCode::no_error)
        {
            //Записать в лог по уровню логирования
            switch (errorLevel)
            {
                case ErrorLevel::fatal:
                    kav::Logger::fatal(completedMessage, OperationException(errorCode, filePath));
                    //Выбросить исключение
                    throw OperationException(errorCode, filePath);
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
};



#endif //SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H/
