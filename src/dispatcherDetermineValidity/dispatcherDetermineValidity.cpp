//
// Created by Alexander on 13.06.2025.
//



#include "dispatcherDetermineValidity.h"



ErrorCode DispatcherDetermineValidity::writeJSONFile(const std::string& filePath, const JSON& objectJSON, ErrorLevel errorLevel,
                                                     const std::string& message, const int formatByWidth, const boost::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::writeJSONFile(filePath, objectJSON, formatByWidth, callingFunction)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

std::pair<JSON, ErrorCode> DispatcherDetermineValidity::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                     const std::string& message,
                                                                     const boost::source_location &callingFunction)
{
    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    std::pair<JSON, ErrorCode> tmp{OperationFileAndJSON::readJSONFile(filePath, callingFunction)};

    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    return {tmp.first, tmp.second};

}

std::pair<std::string, ErrorCode> DispatcherDetermineValidity::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                            const std::string& message,
                                                                            const boost::source_location &callingFunction)
{
    std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;

    std::pair<JSON, ErrorCode> tmp{OperationFileAndJSON::readTextFile(filePath, callingFunction)};

    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    //Прочитать файл документа и вернуть документ
    return {tmp.first, tmp.second};
}

ErrorCode DispatcherDetermineValidity::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                                               ErrorLevel errorLevel, const std::string& message,
                                                               const boost::source_location &callingFunction)
{
    std::cout << "checkJSONStructureMatch: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::checkJSONStructureMatch(filePath, objectJSON, objectJSONTemplate, callingFunction)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkFilePathsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                           const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::checkFilePathsArray(objectJSON, callingFunction)};

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                          const boost::source_location &callingFunction)
{
    std::cout << "checkRequestsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::checkRequestsArray(objectJSON, callingFunction)};

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;
}
