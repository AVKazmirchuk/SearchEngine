//
// Created by Alexander on 25.02.2025.
//



#include <fstream>

#include "readWriteJSONFile.h"



JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    return JSON::parse(file);
}