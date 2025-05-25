//
// Created by Alexander on 31.03.2025.
//

#include <source_location>

#include "checkFile.h"
#include "readWriteJSONFile.h"
#include "logger.h"
#include "boost/current_function.hpp"
#include <ranges>




void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath, const int formatByWidth)
{
    //Создать объект для записи
    std::ofstream outFile{filePath};

    CheckFile::isFileOpenWrite(outFile, filePath, "void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", std::runtime_error("e"));

    //Записать JSON-объект в файл
    outFile << std::setw(formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate, const std::source_location &location)
{

    std::cout << location.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    CheckFile::isJSONStructureValid(inFile, filePath, "JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)", std::runtime_error("e"));

    //Прочитать файл в JSON-объект
    JSON targetJSON = JSON::parse(inFile);

    CheckFile::isJSONStructureMatch(targetJSON, objectJSONTemplate, filePath,
                                    "JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate)",
                                    std::runtime_error("e"));

    //Вернуть JSON-объект
    return targetJSON;
}

