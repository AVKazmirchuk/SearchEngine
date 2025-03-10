//
// Created by Alexander on 25.02.2025.
//



#include <fstream>

#include "readWriteJSONFile.h"



void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)
{
    //Создать объект для записи
    std::ofstream file{filePath};

    //Записать JSON-объект в файл
    file << std::setw(constants::formatByWidth) << objectJSON;
}
