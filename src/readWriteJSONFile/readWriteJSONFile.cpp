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






void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath, const int formatByWidth, const std::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для записи
    std::ofstream outFile{filePath};

    DispatcherOperationValidity::determineWriteJSONFile(outFile, filePath, callingFunction.function_name());

    //Записать JSON-объект в файл
    outFile << std::setw(formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate, const std::source_location &callingFunction)
{

    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    DispatcherOperationValidity::determineReadJSONFile(inFile, filePath, callingFunction.function_name());

    //Прочитать файл в JSON-объект
    JSON targetJSON = JSON::parse(inFile);

    DispatcherOperationValidity::determineJSONStructureMatch(targetJSON, objectJSONTemplate, filePath, callingFunction.function_name());

    //Вернуть JSON-объект
    return targetJSON;
}

