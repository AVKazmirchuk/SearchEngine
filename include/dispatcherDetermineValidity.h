//
// Created by Alexander on 13.06.2025.
//

#ifndef SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H
#define SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H



#include "check/operationFileAndJSON.h"
#include "logger.h"



enum class ErrorLevel
{
    debug,
    info,
    warning,
    error,
    fatal
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



#endif //SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H
