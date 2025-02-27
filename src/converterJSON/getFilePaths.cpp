//
// Created by Alexander on 27.01.2025.
//



#include <iostream>

#include "converterJSON.h"
#include "general.h"



std::vector<std::string> ConverterJSON::getFilePaths()
{
    std::vector<std::string> filePaths(configJSON[constants::filesStr]);

    return filePaths;
}