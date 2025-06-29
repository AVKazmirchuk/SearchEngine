//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include <iostream>
#include <filesystem>

#include "operationFileAndJSON.h"



kav::ErrorCode kav::OperationFileAndJSON::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth, const boost::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для записи
    std::ofstream outFile{filePath};

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!outFile.is_open()) errorCode = ErrorCode::error_file_not_open_write;

    if (errorCode == ErrorCode::no_error)
    {
        //Записать JSON-объект в файл
        outFile << std::setw(formatByWidth) << objectJSON;
    }

    return errorCode;
}

std::pair<JSON, ErrorCode> kav::OperationFileAndJSON::readJSONFile(const std::string& filePath, const boost::source_location &callingFunction)
{
    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    JSON objectJSON;

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;
        //else if (!CheckJSON::isJSONStructureValid(inFile)) errorCode = ErrorCode::error_json_structure_corrupted;
    else if ((objectJSON = JSON::parse(inFile, nullptr, false)).is_discarded()) errorCode = ErrorCode::error_json_structure_corrupted;

    return {objectJSON, errorCode};
}

std::pair<std::string, kav::ErrorCode> kav::OperationFileAndJSON::readTextFile(const std::string& filePath, const boost::source_location &callingFunction)
{
    std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;

    //Прочитать файл документа и вернуть документ
    if (errorCode == ErrorCode::no_error) return {{(std::istreambuf_iterator<char>(inFile)), {}}, errorCode};
    return {{}, errorCode};
}

kav::ErrorCode kav::OperationFileAndJSON::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                                        const boost::source_location &callingFunction)
{
    std::cout << "checkJSONStructureMatch: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (!CheckJSON::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::error_json_structure_not_match;

    return errorCode;
}

kav::ErrorCode kav::OperationFileAndJSON::checkFilePathsArray(const JSON& objectJSON, const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (objectJSON.empty()) errorCode = ErrorCode::error_file_paths_array_empty;

    return errorCode;
}

kav::ErrorCode kav::OperationFileAndJSON::checkRequestsArray(const JSON& objectJSON, const boost::source_location &callingFunction)
{
    std::cout << "checkFilePathsArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (objectJSON.empty()) errorCode = ErrorCode::error_requests_array_empty;

    return errorCode;
}

