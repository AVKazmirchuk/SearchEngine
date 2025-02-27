//
// Created by Alexander on 25.02.2025.
//



#include <fstream>

#include "readWriteJSONFile.h"



ordered_float_json ReadWriteJSONFile::readJSONFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    return ordered_float_json::parse(file);
}