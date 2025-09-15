//
// Created by Alexander on 13.06.2025.
//

#ifndef SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H
#define SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H



#include "kav/operationFileAndJSON.h"
#include "kav/logger.h"
#include "general.h"



enum class ErrorLevel
{
    no_level,
    debug,
    info,
    warning,
    error,
    fatal
};

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
 * Класс реализует генерацию исключений
 */
class CheckFileException : public std::exception
{

public:

    /**
     * Инициализирует код исключения
     * @param in_errorCode Код исключения
     * @param in_information Информация по исключению
     */
    explicit CheckFileException(ErrorCode in_errorCode, const std::string &in_information = "") : errorCode(
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
        return errorCode;
    }

private:

    ErrorCode errorCode;
    std::string information;

};



class DispatcherDetermineValidity
{

public:

    static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON,
                                   ErrorLevel errorLevel = ErrorLevel::no_level, const std::string &message = "",
                                   const int formatByWidth = 2,
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode
    checkJSONStructureMatch(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                            ErrorLevel errorLevel = ErrorLevel::no_level, const std::string &message = "",
                            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);


    static ErrorCode checkFilePathsArray(JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::no_level,
                                         const std::string &message = "",
                                         const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static ErrorCode checkRequestsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::no_level,
                                        const std::string &message = "",
                                        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Прочитать JSON-файл
     * @param filePath Путь JSON-файла
     * @return JSON-файл
     */
    static std::pair<JSON, ErrorCode>
    readJSONFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::no_level,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static std::pair<std::string, ErrorCode>
    readTextFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::no_level,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static std::pair<std::vector<std::string>, ErrorCode> readMultipleTextFiles(const std::vector<std::string>& filePaths, ErrorLevel errorLevel = ErrorLevel::no_level,
                                                                                    const std::string &message = "",
                                                                                    const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

private:

    static const ErrorCode convertErrorCodeFrom(const kav::ErrorCode errorCode)
    {
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

        return matchingErrorCodes.at(errorCode);

    }

    static const ErrorLevel getErrorLevelFrom(const std::string& functionName)
    {
        const std::map<std::string, ErrorLevel> matchingFunctionNameAndErrorLevel{
                {"SearchEngine::ConfigSearchEngine::initialize",       ErrorLevel::fatal},
                {"ConverterJSON::checkFilePath",                       ErrorLevel::fatal},
                {"ConverterJSON::checkRequests",                       ErrorLevel::fatal},
                {"DispatcherDetermineValidity::readMultipleTextFiles", ErrorLevel::error},
                {"SearchEngine::readDocsFromFiles",                    ErrorLevel::fatal},
                {"SearchEngine::writeAnswersToFile",                   ErrorLevel::fatal}
        };

        return matchingFunctionNameAndErrorLevel.at(functionName);
    }

    static ErrorLevel getFunctionName(const std::string& callingFunctionStr)
    {
        std::string::size_type endNameFunction{callingFunctionStr.find('(') - 1};
        std::string::size_type beginNameFunction{endNameFunction};
        std::string::size_type symbolsNumber{};

        for (; callingFunctionStr[beginNameFunction] != ' '; --beginNameFunction, ++symbolsNumber)
        {

        }

        //if (callingFunctionStr.substr(beginNameFunction, endNameFunction).find("eadTextFile::readTextFil") != std::string::npos)
        //{
        //std::cout << "\n!!!" << callingFunctionStr.substr(beginNameFunction + 1, symbolsNumber) << " - " << static_cast<int>(errorLevel) << "!!!\n";
        //}

        return getErrorLevelFrom(callingFunctionStr.substr(beginNameFunction + 1, symbolsNumber));
    }

    static void determineValidity(const std::string &filePath, ErrorCode errorCode = ErrorCode::no_error,
                                  ErrorLevel errorLevel = ErrorLevel::no_level,
                                  const std::string &message = "",
                                  const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION)
    {
        std::string callingFunctionStr{callingFunction.to_string()};

        if (errorLevel == ErrorLevel::no_level)
        {
            errorLevel = getFunctionName(callingFunctionStr);
            //if (filePath == "config.json") std::cout << static_cast<int>(errorLevel);
        }

        std::string completedMessage{descriptionErrorCode.at(errorCode) + ": " + filePath + ". " +
                                     static_cast<std::string>("Calling function: ") + callingFunctionStr + ". " + message};
        //if (errorCode != ErrorCode::no_error ||
        //    (errorCode == ErrorCode::no_error && errorLevel != ErrorLevel::no_level &&
        //    errorLevel != ErrorLevel::fatal && errorLevel != ErrorLevel::error && errorLevel != ErrorLevel::warning))
        if (errorCode != ErrorCode::no_error)
        {
            //if (filePath == "config.json") std::cout << static_cast<int>(errorLevel);
            switch (errorLevel)
            {
                case ErrorLevel::fatal:
                    kav::Logger::fatal(completedMessage, CheckFileException(errorCode, filePath));
                    throw CheckFileException(errorCode, filePath);
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
