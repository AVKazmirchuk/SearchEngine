//
// Created by Alexander on 31.03.2025.
//


#include "checkFile.h"
#include "readWriteJSONFile.h"
#include "logger.h"



void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath, const int formatByWidth)
{
    //Создать объект для записи
    std::ofstream outFile{filePath};

    CheckFile::isFileOpenWrite(outFile, filePath, "void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", std::runtime_error("e"));

    //Записать JSON-объект в файл
    outFile << std::setw(formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate, std::string str)
{
    std::cout << str << std::endl;

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

