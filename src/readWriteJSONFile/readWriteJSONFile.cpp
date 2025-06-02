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

    //std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);



    if (!DispatcherOperationValidity::determineReadJSONFile(filePath, inFile, message, errorLevel, callingFunction))
    {
        return {};
    }

    //Прочитать файл в JSON-объект
    JSON targetJSON = JSON::parse(inFile);

    //if (DispatcherOperationValidity::determineJSONStructureMatch(filePath, targetJSON, objectJSONTemplate, message, errorLevel, callingFunction))

    //Вернуть JSON-объект
    return targetJSON;
}

