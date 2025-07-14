//
// Created by Alexander on 13.06.2025.
//

#ifndef SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H
#define SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H



#include "kav/operationFileAndJSON.h"
#include "kav/logger/logger.h"
#include "general.h"


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

    static kav::ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON,
                                   ErrorLevel errorLevel = ErrorLevel::fatal, const std::string &message = "",
                                   const int formatByWidth = 2,
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static kav::ErrorCode
    checkJSONStructureMatch(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                            ErrorLevel errorLevel = ErrorLevel::fatal, const std::string &message = "",
                            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);


    static kav::ErrorCode checkFilePathsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::fatal,
                                         const std::string &message = "",
                                         const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static kav::ErrorCode checkRequestsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::fatal,
                                        const std::string &message = "",
                                        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Прочитать JSON-файл
     * @param filePath Путь JSON-файла
     * @return JSON-файл
     */
    static std::pair<JSON, kav::ErrorCode>
    readJSONFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::fatal,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    static std::pair<std::string, kav::ErrorCode>
    readTextFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::fatal,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

private:

    static void determineValidity(const std::string &filePath, kav::ErrorCode errorCode = kav::ErrorCode::no_error,
                                  ErrorLevel errorLevel = ErrorLevel::fatal,
                                  const std::string &message = "",
                                  const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION)
    {
        std::string completedMessage{kav::descriptionErrorCode.at(errorCode) + ": " + filePath + ". " +
                                     static_cast<std::string>("Calling function: ") + callingFunction.to_string() + ". " + message};

        if (errorCode != kav::ErrorCode::no_error)
        {
            switch (errorLevel)
            {
                case ErrorLevel::fatal:
                    kav::Logger::fatal(completedMessage, kav::CheckFileException(errorCode, filePath));
                    throw kav::CheckFileException(errorCode, filePath);
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



#endif //SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H
