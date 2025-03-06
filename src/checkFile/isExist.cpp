//
// Created by Alexander on 27.01.2025.
//



#include "checkFile.h"



bool CheckFile::isExist(const std::string &fileName)
{
    return std::filesystem::exists(fileName);
}