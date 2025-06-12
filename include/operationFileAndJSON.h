//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_OPERATIONFILEANDJSON_H
#define SEARCH_ENGINE_OPERATIONFILEANDJSON_H



#include <fstream>

#include "boost/assert/source_location.hpp"
#include "nlohmann/json.hpp"

#include "logger.h"



enum class ErrorLevel
{
    debug,
    info,
    warning,
    error,
    fatal
};

/**
 * Класс реализует проверку файла и его содержимого (JSON-структуру)
 */
class CheckJSON
{

public:

    CheckJSON() = delete;

    /**
     * Проверить JSON-структуру файла на соответствие шаблону
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);

private:

    class JSONStructureNotMatch {};

    /**
     * Проверить JSON-структуру файла на соответствие шаблону (реализация)
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static bool isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate);

};

/**
 * Класс реализует чтение и запись JSON-файлов
 */
class OperationFileAndJSON
{

public:

    OperationFileAndJSON() = delete;


    /**
     * Записать JSON-файл
     * @param objectJSON JSON-объект
     * @param filePath Путь JSON-файла
     */
    static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const int formatByWidth = 2,
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode checkJSONStructureMatch(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                                             const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);


    static ErrorCode checkFilePathsArray(const JSON &objectJSON, const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode checkRequestsArray(const JSON &objectJSON, const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Прочитать JSON-файл
     * @param filePath Путь JSON-файла
     * @return JSON-файл
     */
    static std::pair<JSON, ErrorCode> readJSONFile(const std::string &filePath, const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static std::pair<std::string, ErrorCode> readTextFile(const std::string &filePath, const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

};



class DispatcherDetermineValidity
{

public:

    static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON,
                                   ErrorLevel errorLevel = ErrorLevel::fatal, const std::string &message = "",
                                   const int formatByWidth = 2,
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode
    checkJSONStructureMatch(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                            ErrorLevel errorLevel = ErrorLevel::fatal, const std::string &message = "",
                            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);


    static ErrorCode checkFilePathsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::fatal,
                                         const std::string &message = "",
                                         const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode checkRequestsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::fatal,
                                        const std::string &message = "",
                                        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Прочитать JSON-файл
     * @param filePath Путь JSON-файла
     * @return JSON-файл
     */
    static std::pair<JSON, ErrorCode>
    readJSONFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::fatal,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static std::pair<std::string, ErrorCode>
    readTextFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::fatal,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

private:

    static void determineValidity(const std::string &filePath, ErrorCode errorCode = ErrorCode::no_error,
                                  ErrorLevel errorLevel = ErrorLevel::fatal,
                                  const std::string &message = "",
                                  const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION)
    {
        std::string completedMessage{descriptionErrorCode.at(errorCode) + ": " + filePath + ". " +
                static_cast<std::string>("Calling function: ") + callingFunction.to_string() + ". " + message};

        if (errorCode != ErrorCode::no_error)
        {
            switch (errorLevel)
            {
                case ErrorLevel::fatal:
                    Logger::fatal(completedMessage, CheckFileException(errorCode, filePath));
                    throw CheckFileException(errorCode, filePath);
                case ErrorLevel::error:
                    Logger::error(completedMessage);
                    return;
                case ErrorLevel::warning:
                    Logger::warning(completedMessage);
                    return;
                case ErrorLevel::info:
                    Logger::info(completedMessage);
                    return;
                case ErrorLevel::debug:
                    Logger::debug(completedMessage);
                    return;
            }
        }
    }
};



#endif //SEARCH_ENGINE_OPERATIONFILEANDJSON_H
