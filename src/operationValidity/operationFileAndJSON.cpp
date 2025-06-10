//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>

#include "operationFileAndJSON.h"
#include "logger.h"



ErrorCode OperationFileAndJSON::writeJSONFile(const std::string& filePath, const JSON& objectJSON, ErrorLevel errorLevel,
                                           const std::string& message, const int formatByWidth, const boost::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для записи
    std::ofstream outFile{filePath};

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!outFile.is_open()) errorCode = ErrorCode::error_file_not_open_write;

    if (returnOfResult(errorCode))
    {
        //Записать JSON-объект в файл
        outFile << std::setw(formatByWidth) << objectJSON;
    }

    determineDegreeOfValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

tl::expected<JSON, ErrorCode> OperationFileAndJSON::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
                                                              const std::string& message,
                                                              const boost::source_location &callingFunction)
{
    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    JSON objectJSON;

    //objectJSON = DispatcherOperationValidity::determineReadJSONFile(filePath, inFile, message, errorLevel, callingFunction);

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;
        //else if (!CheckJSON::isJSONStructureValid(inFile)) errorCode = ErrorCode::error_json_structure_corrupted;
    else if ((objectJSON = JSON::parse(inFile, nullptr, false)).is_discarded()) errorCode = ErrorCode::error_json_structure_corrupted;

    //determineDegreeOfValidity(filePath, errorCode, message, errorLevel, callingFunction);


    if (errorCode == ErrorCode::no_error) return objectJSON;
    return tl::unexpected(errorCode);
    //return returnOfResult(errorCode) ? objectJSON : std::unexpected(errorCode);
}

tl::expected<std::string, ErrorCode> OperationFileAndJSON::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                     const std::string& message,
                                                                     const boost::source_location &callingFunction)
{
    std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;

    determineDegreeOfValidity(filePath, errorCode, errorLevel, message, callingFunction);

    //Прочитать файл документа и вернуть документ
    if (returnOfResult(errorCode)) return std::string({(std::istreambuf_iterator<char>(inFile)), {}});
    return tl::unexpected(errorCode);
}

ErrorCode OperationFileAndJSON::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                              ErrorLevel errorLevel, const std::string& message,
                                       const boost::source_location &callingFunction)
{
    std::cout << "checkJSON: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (!CheckJSON::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::error_json_structure_not_match;

    determineDegreeOfValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode OperationFileAndJSON::checkFilePathsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                 const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (objectJSON.empty()) errorCode = ErrorCode::error_file_paths_array_empty;

    determineDegreeOfValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;

}

ErrorCode OperationFileAndJSON::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (objectJSON.empty()) errorCode = ErrorCode::error_requests_array_empty;

    determineDegreeOfValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;

}



ErrorCode DispatcherDetermineValidity::writeJSONFile(const std::string& filePath, const JSON& objectJSON, ErrorLevel errorLevel,
                                              const std::string& message, const int formatByWidth, const boost::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::writeJSONFile(filePath, objectJSON, errorLevel, message, formatByWidth, callingFunction)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

tl::expected<JSON, ErrorCode> DispatcherDetermineValidity::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                 const std::string& message,
                                                                 const boost::source_location &callingFunction)
{
    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    JSON objectJSON;

    //objectJSON = DispatcherOperationValidity::determineReadJSONFile(filePath, inFile, message, errorLevel, callingFunction);

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;
        //else if (!CheckJSON::isJSONStructureValid(inFile)) errorCode = ErrorCode::error_json_structure_corrupted;
    else if ((objectJSON = JSON::parse(inFile, nullptr, false)).is_discarded()) errorCode = ErrorCode::error_json_structure_corrupted;

    determineValidity(filePath, errorCode, message, errorLevel, callingFunction);


    if (errorCode == ErrorCode::no_error) return objectJSON;
    return tl::unexpected(errorCode);
    //return returnOfResult(errorCode) ? objectJSON : std::unexpected(errorCode);
}

tl::expected<std::string, ErrorCode> DispatcherDetermineValidity::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                        const std::string& message,
                                                                        const boost::source_location &callingFunction)
{
    std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;

    determineDegreeOfValidity(filePath, errorCode, errorLevel, message, callingFunction);

    //Прочитать файл документа и вернуть документ
    if (returnOfResult(errorCode)) return std::string({(std::istreambuf_iterator<char>(inFile)), {}});
    return tl::unexpected(errorCode);
}

ErrorCode DispatcherDetermineValidity::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                                        ErrorLevel errorLevel, const std::string& message,
                                                        const boost::source_location &callingFunction)
{
    std::cout << "checkJSON: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::checkJSONStructureMatch(filePath, objectJSON, objectJSONTemplate, errorLevel, message, callingFunction)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkFilePathsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                    const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::checkFilePathsArray(objectJSON, errorLevel, message, callingFunction)};

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;

}

ErrorCode DispatcherDetermineValidity::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                   const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{OperationFileAndJSON::checkRequestsArray(objectJSON, errorLevel, message, callingFunction)};

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;

}
