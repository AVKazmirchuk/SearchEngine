//
// Created by Alexander on 28.01.2025.
//



#include "checkFile.h"
#include "general.h"



bool CheckFile::isEmpty(const std::string &fileName)
{
    //Вернуть признак существования файла
    return std::filesystem::is_empty(fileName);
}

