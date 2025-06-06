//
// Created by Alexander on 07.05.2025.
//



#include <fstream>

#include "readWriteJSONFile.h"
#include "checkFileException.h"


void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)
{
    //Создать объект для записи
    std::ofstream file{filePath};

    //Проверить файл на открытие для записи
    if (!file.is_open())
    {
        //TODO Logger::fatal("void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", CheckFileException(ErrorCode::error_file_not_open_write, filePath));
        //TODO throw CheckFileException(ErrorCode::error_file_not_open_write, filePath);
    }

    //Записать JSON-объект в файл
    //TODO file << std::setw(constants::formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)
{
    //Создать объект для чтения
    std::ifstream file(filePath);

    //Проверить файл на открытие для чтения
    if (!file.is_open())
    {
        //TODO Logger::fatal("JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)", CheckFileException(ErrorCode::error_file_not_open_read, filePath));
        //TODO throw CheckFileException(ErrorCode::error_file_not_open_read, filePath);
    }

    //Прочитать файл в JSON-объект и вернуть объект
    return JSON::parse(file);
}