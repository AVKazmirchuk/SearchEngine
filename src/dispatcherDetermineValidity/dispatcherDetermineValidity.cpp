//
// Created by Alexander on 13.06.2025.
//



#include "dispatcherDetermineValidity.h"



ErrorCode DispatcherDetermineValidity::writeJSONFile(const std::string& filePath, const JSON& objectJSON, ErrorLevel errorLevel,
                                                     const std::string& message, const int formatByWidth, const boost::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::writeJSONFile(filePath, objectJSON, formatByWidth, callingFunction)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

std::pair<JSON, ErrorCode> DispatcherDetermineValidity::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                     const std::string& message,
                                                                     const boost::source_location &callingFunction)
{
    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    std::pair<JSON, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readJSONFile(filePath, callingFunction)};

    std::pair<JSON, ErrorCode> tmp{std::move(tmpOriginal.first), convertErrorCodeFrom(tmpOriginal.second)};

    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    return tmp;

}

std::pair<std::string, ErrorCode> DispatcherDetermineValidity::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                            const std::string& message,
                                                                            const boost::source_location &callingFunction)
{
    std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;

    std::pair<std::string, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readTextFile(filePath, callingFunction)};

    std::pair<std::string, ErrorCode> tmp{std::move(tmpOriginal.first), convertErrorCodeFrom(tmpOriginal.second)};

    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    return tmp;
}

ErrorCode DispatcherDetermineValidity::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                                               ErrorLevel errorLevel, const std::string& message,
                                                               const boost::source_location &callingFunction)
{
    std::cout << "checkJSONStructureMatch: " << callingFunction.function_name() << std::endl;

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkJSONStructureMatch(filePath, objectJSON, objectJSONTemplate, callingFunction)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkFilePathsArray(JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                           const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkArray(objectJSON, callingFunction)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    if (errorCode == ErrorCode::error_array_empty)
    {
        errorCode = ErrorCode::error_file_paths_array_empty;
    }

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    /*if (errorCode != ErrorCode::error_file_paths_array_empty)
    {
        for (std::size_t idx{}; idx < objectJSON.size(); ++idx)
        {
            if (!std::filesystem::exists(objectJSON[idx]))
            {
                auto missingFile = objectJSON[idx];

                objectJSON.erase(idx);
                --idx;

                errorCode = ErrorCode::error_file_missing;

                determineValidity(missingFile, errorCode, ErrorLevel::error, "File " + std::string(missingFile) + " is missing!", callingFunction);
            }
        }
    }*/

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                          const boost::source_location &callingFunction)
{
    std::cout << "checkRequestsArray: " << callingFunction.function_name() << std::endl;

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkArray(objectJSON, callingFunction)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    if (errorCode == ErrorCode::error_array_empty)
    {
        errorCode = ErrorCode::error_requests_array_empty;
    }

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkAllFilesHaveErrors(const std::string& message, const boost::source_location &callingFunction)
{
    std::cout << "checkAllFilesHaveErrors: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::error_all_files_have_errors};

    ErrorLevel errorLevel{ErrorLevel::info};

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;
}
