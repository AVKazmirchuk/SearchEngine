//
// Created by Alexander on 31.03.2025.
//



#include "readWriteJSONFile.h"
#include "logger.h"



void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)
{
    //Создать объект для записи
    std::ofstream file{filePath};

    //Проверить файл на открытие для записи
    if (!file.is_open())
    {
        Logger::fatal("void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_WRITE, filePath));
        throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_WRITE, filePath);
    }

    //Записать JSON-объект в файл
    file << std::setw(constants::formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)
{
    //Создать объект для чтения
    std::ifstream file(filePath);

    //Проверить файл на открытие для чтения
    /*if (!file.is_open())
    {
        Logger::fatal("JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)", CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath));
        throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath);
    }*/

    //Прочитать файл в JSON-объект и вернуть объект
    return JSON::parse(file);
}