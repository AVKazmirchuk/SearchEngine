//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_OPERATIONVALIDITY_H
#define SEARCH_ENGINE_OPERATIONVALIDITY_H



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
     * Прочитать JSON-файл
     * @param filePath Путь JSON-файла
     * @return JSON-файл
     */
    static JSON readJSONFile(const std::string& filePath, const std::string& message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                             const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Записать JSON-файл
     * @param objectJSON JSON-объект
     * @param filePath Путь JSON-файла
     */
    static bool writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth = 2,
                              const std::string& message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                              const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static bool checkJSON(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                      const std::string& message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                          const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static std::string readTextFile(const std::string& filePath, const std::string& message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                                    const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static bool checkFilePathsArray(const JSON& objectJSON,
                                    const std::string& message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                                    const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static bool checkRequestsArray(const JSON& objectJSON,
                                    const std::string& message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

private:

    class DispatcherOperationValidity
    {

    public:

        static bool determineJSONStructureMatch(const std::string& filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                                                const std::string& message, ErrorLevel errorLevel, const boost::source_location &callingFunction)
        {
            ErrorCode errorCode{ErrorCode::no_error};

            if (!CheckJSON::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::error_json_structure_not_match;

            determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

            return returnOfResult(errorCode);
        }

        static bool determineFilePathsArrayEmpty(const JSON &objectJSON, const std::string& message,
                                                 ErrorLevel errorLevel, const boost::source_location &callingFunction)
        {
            ErrorCode errorCode{ErrorCode::no_error};

            if (objectJSON.empty()) errorCode = ErrorCode::error_file_paths_array_empty;

            determineDegreeOfValidity("", errorCode, message, errorLevel, callingFunction);

            return returnOfResult(errorCode);
        }

        static bool determineRequestsArrayEmpty(const JSON &objectJSON, const std::string& message,
                                                ErrorLevel errorLevel, const boost::source_location &callingFunction)
        {
            ErrorCode errorCode{ErrorCode::no_error};

            if (objectJSON.empty()) errorCode = ErrorCode::error_requests_array_empty;

            determineDegreeOfValidity("", errorCode, message, errorLevel, callingFunction);

            return returnOfResult(errorCode);
        }

        static bool determineReadFile(const std::string& filePath, std::ifstream& inFile, const std::string& message,
                                      ErrorLevel errorLevel, const boost::source_location &callingFunction)
        {
            ErrorCode errorCode{ErrorCode::no_error};

            if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
            else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;

            determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

            return returnOfResult(errorCode);
        }

        static bool determineReadJSONFile(const std::string& filePath, std::ifstream& inFile, const std::string& message,
                                          ErrorLevel errorLevel, const boost::source_location &callingFunction)
        {
            ErrorCode errorCode{ErrorCode::no_error};

            if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
            else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;
            else if (!CheckJSON::isJSONStructureValid(inFile)) errorCode = ErrorCode::error_json_structure_corrupted;

            determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

            return returnOfResult(errorCode);
        }


        static bool determineWriteJSONFile(const std::string& filePath, std::ofstream& outFile, const std::string& message,
                                           ErrorLevel errorLevel, const boost::source_location &callingFunction)
        {
            ErrorCode errorCode{ErrorCode::no_error};

            if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
            else if (!outFile.is_open()) errorCode = ErrorCode::error_file_not_open_write;

            determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

            return returnOfResult(errorCode);
        }

    private:

        static void determineDegreeOfValidity(const std::string& filePath, ErrorCode errorCode, const std::string& message,
                                              ErrorLevel errorLevel, const boost::source_location &callingFunction)
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
};



#endif //SEARCH_ENGINE_OPERATIONVALIDITY_H
