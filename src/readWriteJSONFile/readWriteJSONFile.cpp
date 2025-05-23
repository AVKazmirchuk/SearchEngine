//
// Created by Alexander on 31.03.2025.
//


#include "checkFile.h"
#include "readWriteJSONFile.h"
#include "logger.h"



void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)
{
    //Создать объект для записи
    std::ofstream outFile{filePath};

    //Проверить файл на открытие для записи
    //if (!outFile.is_open())
    //{
    //    Logger::fatal("void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_WRITE, filePath));
    //    throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_WRITE, filePath);
    //}

    CheckFile::isFileOpenWrite(outFile, filePath, "void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", std::runtime_error("e"));

    //Записать JSON-объект в файл
    outFile << std::setw(constants::formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate)
{
    //Создать объект для чтения
    std::ifstream inFile(filePath);

    CheckFile::isJSONStructureValid(inFile, filePath, "JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)", std::runtime_error("e"));

    JSON targetJSON = JSON::parse(inFile);
    std::cout << "qwerty" << std::endl;
    //CheckFile::isJSONStructureMatch(targetJSON, objectJSONTemplate, filePath,
    //                                "JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate)",
    //                                std::runtime_error("e"));

    //Прочитать файл в JSON-объект и вернуть объект
    //return targetJSON;
    return JSON::parse(inFile);
}

//https://stackoverflow.com/questions/28331017/rewind-an-ifstream-object-after-hitting-the-end-of-file