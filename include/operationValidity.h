//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_OPERATIONVALIDITY_H
#define SEARCH_ENGINE_OPERATIONVALIDITY_H



#include <fstream>
//#include <expected>

#include "boost/assert/source_location.hpp"
#include "expected.hpp"
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
     * Проверить файл на целостность JSON-структуры
     * @param fileName Имя файла
     * @return Файл целостный(true)/не целостный(false)
     */
    static bool isJSONStructureValid(std::ifstream& inFile);

    /**
     * Проверить JSON-структуру файла на соответствие шаблону
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);

private:

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
class OperationValidity
{

public:

    OperationValidity() = delete;


    /**
     * Записать JSON-файл
     * @param objectJSON JSON-объект
     * @param filePath Путь JSON-файла
     */
    static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const int formatByWidth = 2,
                                   const std::string &message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode checkJSON(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                               const std::string &message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                               const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);


    static ErrorCode checkFilePathsArray(const JSON &objectJSON,
                                         const std::string &message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                                         const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode checkRequestsArray(const JSON &objectJSON,
                                        const std::string &message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                                        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Прочитать JSON-файл
     * @param filePath Путь JSON-файла
     * @return JSON-файл
     */
    static tl::expected<JSON, ErrorCode> readJSONFile(const std::string &filePath, const std::string &message = "",
                                                      ErrorLevel errorLevel = ErrorLevel::fatal,
                                                      const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static tl::expected<std::string, ErrorCode>
    readTextFile(const std::string &filePath, const std::string &message = "",
                 ErrorLevel errorLevel = ErrorLevel::fatal,
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

private:

    static void determineDegreeOfValidity(const std::string &filePath, ErrorCode errorCode, const std::string &message,
                                          ErrorLevel errorLevel, const boost::source_location &callingFunction)
    {
        std::string completedMessage{
                static_cast<std::string>("Calling function: ") + callingFunction.to_string() + ". " + message};

        if (errorCode != ErrorCode::no_error)
        {
            switch (errorLevel)
            {
                case ErrorLevel::fatal:
                    Logger::fatal(completedMessage, CheckFileException(errorCode, filePath));
                    throw CheckFileException(errorCode, filePath);
                case ErrorLevel::error:
                    Logger::error(completedMessage, CheckFileException(errorCode, filePath));
                    return;
                case ErrorLevel::warning:
                    Logger::warning(completedMessage, CheckFileException(errorCode, filePath));
                    return;
                case ErrorLevel::info:
                    Logger::info(completedMessage, CheckFileException(errorCode, filePath));
                    return;
                case ErrorLevel::debug:
                    Logger::debug(completedMessage, CheckFileException(errorCode, filePath));
                    return;
            }
        }
    }

    static bool returnOfResult(ErrorCode errorCode)
    {
        if (errorCode != ErrorCode::no_error)
        {
            return false;
        } else
        {
            return true;
        }
    }

};


    class DispatcherOperationValidity
    {

    public:




        static void determineDegreeOfValidity(const std::string &filePath, ErrorCode errorCode = ErrorCode::no_error,
                                              ErrorLevel errorLevel = ErrorLevel::fatal,
                                              const std::string &message = "",
                                              const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION)
        {
            std::string completedMessage{static_cast<std::string>("Calling function: ") + callingFunction.to_string() + ". " + message};

            if (errorCode != ErrorCode::no_error)
            {
                switch (errorLevel)
                {
                    case ErrorLevel::fatal:
                        Logger::fatal(completedMessage, CheckFileException(errorCode, filePath));
                        throw CheckFileException(errorCode, filePath);
                    case ErrorLevel::error:
                        Logger::error(completedMessage, CheckFileException(errorCode, filePath));
                        return;
                    case ErrorLevel::warning:
                        Logger::warning(completedMessage, CheckFileException(errorCode, filePath));
                        return;
                    case ErrorLevel::info:
                        Logger::info(completedMessage, CheckFileException(errorCode, filePath));
                        return;
                    case ErrorLevel::debug:
                        Logger::debug(completedMessage, CheckFileException(errorCode, filePath));
                        return;
                }
            }
        }

        static bool returnOfResult(ErrorCode errorCode)
        {
            if (errorCode != ErrorCode::no_error)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    };




#endif //SEARCH_ENGINE_OPERATIONVALIDITY_H
