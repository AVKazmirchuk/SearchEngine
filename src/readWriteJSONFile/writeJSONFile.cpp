//
// Created by Alexander on 25.02.2025.
//



#include <fstream>

#include "readWriteJSONFile.h"



void ReadWriteJSONFile::writeJSONFile(const ordered_float_json& objectJSON, const std::string& filePath, int formatByWidth)
{
    std::ofstream file{filePath};

    file << std::setw(formatByWidth) << objectJSON;
}