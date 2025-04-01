//
// Created by Alexander on 31.03.2025.
//



#include "readWriteJSONFile.h"



void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)
{
    //Создать объект для записи
    std::ofstream file{filePath};

    //Записать JSON-объект в файл
    file << std::setw(constants::formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)
{
    //Создать объект для чтения
    std::ifstream file(filePath);

    //Прочитать файл в JSON-объект и вернуть объект
    return JSON::parse(file);
}