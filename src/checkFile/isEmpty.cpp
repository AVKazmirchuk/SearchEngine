//
// Created by Alexander on 28.01.2025.
//



#include "checkFile.h"
#include "general.h"



bool CheckFile::isEmpty(const std::string &fileName)
{
    return std::filesystem::is_empty(fileName);
}


/*
bool checkFileEmpty()
{
    return objectJSON.contains(constants::configStr);
}*/