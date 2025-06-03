//
// Created by Alexander on 31.03.2025.
//

#include <source_location>
#include <algorithm>
#include <list>

#include "checkFile.h"
#include "readWriteJSONFile.h"
#include "logger.h"
#include "boost/current_function.hpp"
#include "checkFileException.h"






bool ReadWriteJSONFile::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth,
                                      const std::string& message, ErrorLevel errorLevel, const std::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для записи
    std::ofstream outFile{filePath};

    if (!DispatcherOperationValidity::determineWriteJSONFile(filePath, outFile, message, errorLevel, callingFunction))
    {
        return false;
    }

    //Записать JSON-объект в файл
    outFile << std::setw(formatByWidth) << objectJSON;

    return true;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const std::string& message, ErrorLevel errorLevel,
                                     const std::source_location &callingFunction)
{

    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    if (!DispatcherOperationValidity::determineReadJSONFile(filePath, inFile, message, errorLevel, callingFunction))
    {
        return {};
    }

    //Прочитать файл в JSON-объект
    //JSON targetJSON = JSON::parse(inFile);

    //Вернуть JSON-объект
    return JSON::parse(inFile);
}

bool ReadWriteJSONFile::checkJSON(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate, const std::string& message, ErrorLevel errorLevel,
                                     const std::source_location &callingFunction)
{
    if (!DispatcherOperationValidity::determineJSONStructureMatch(filePath, objectJSON, objectJSONTemplate, message, errorLevel, callingFunction))
    {
        return false;
    }

    return true;
}

std::string ReadWriteJSONFile::readTextFile(const std::string& filePath, const std::string& message, ErrorLevel errorLevel,
                         const std::source_location &callingFunction)
{
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;
    DispatcherOperationValidity::determineReadFile(filePath, inFile, message, errorLevel, callingFunction);

    //Прочитать файл документа и вернуть документ
    return {(std::istreambuf_iterator<char>(inFile)), {}};
}

