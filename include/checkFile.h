//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_CHECKFILE_H
#define SEARCH_ENGINE_CHECKFILE_H



#include <filesystem>
#include <fstream>
#include <source_location>

#include "nlohmann/json.hpp"

#include "checkFileException.h"
#include "general.h"
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
class CheckFile
{

public:

    CheckFile() = delete;

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



class DispatcherOperationValidity
{

public:

    static bool determineJSONStructureMatch(const std::string& filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                                            const std::string& message, ErrorLevel errorLevel, const std::source_location &callingFunction)
    {
        ErrorCode errorCode{};

        if (!CheckFile::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH;

        determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

        return returnOfResult(errorCode);
    }

    static bool determineFilePathsArrayEmpty(const JSON &objectJSON, const std::string& message,
                                             ErrorLevel errorLevel, const std::source_location &callingFunction)
    {
        ErrorCode errorCode{};

        if (objectJSON.empty()) errorCode = ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY;

        determineDegreeOfValidity("", errorCode, message, errorLevel, callingFunction);

        return returnOfResult(errorCode);
    }

    static bool determineRequestsArrayEmpty(const JSON &objectJSON, const std::string& message,
                                            ErrorLevel errorLevel, const std::source_location &callingFunction)
    {
        ErrorCode errorCode{};

        if (objectJSON.empty()) errorCode = ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY;

        determineDegreeOfValidity("", errorCode, message, errorLevel, callingFunction);

        return returnOfResult(errorCode);
    }

    static bool determineReadFile(const std::string& filePath, std::ifstream& inFile, const std::string& message,
                                  ErrorLevel errorLevel, const std::source_location &callingFunction)
    {
        ErrorCode errorCode{};

        if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!inFile.is_open()) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_READ;

        determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

        return returnOfResult(errorCode);
    }

    static bool determineReadJSONFile(const std::string& filePath, std::ifstream& inFile, const std::string& message,
                                      ErrorLevel errorLevel, const std::source_location &callingFunction)
    {
        ErrorCode errorCode{ErrorCode::ERROR_NO_ERROR};

        if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!inFile.is_open()) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_READ;
        else if (!CheckFile::isJSONStructureValid(inFile)) errorCode = ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED;

        determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

        return returnOfResult(errorCode);
    }


    static bool determineWriteJSONFile(const std::string& filePath, std::ofstream& outFile, const std::string& message,
                                       ErrorLevel errorLevel, const std::source_location &callingFunction)
    {
        ErrorCode errorCode{};

        if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!outFile.is_open()) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_WRITE;

        determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);

        return returnOfResult(errorCode);
    }

private:

    static void determineDegreeOfValidity(const std::string& filePath, ErrorCode errorCode, const std::string& message,
                                          ErrorLevel errorLevel, const std::source_location &callingFunction)
    {
        std::string completedMessage{"Calling function: " + callingFunction.function_name() + ". " + message};

        if (static_cast<int>(errorCode))
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
        if (static_cast<int>(errorCode))
        {
            return false;
        }
        else
        {
            return true;
        }
    }

};



#endif //SEARCH_ENGINE_CHECKFILE_H

