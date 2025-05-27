//
// Created by Alexander on 31.03.2025.
//



#include "converterJSON.h"
#include <iostream>



void ConverterJSON::initialize()
{
    checkFilePath();
    checkRequests();
}

std::string ConverterJSON::about()
{
    //Вернуть строку о программе (название, версия)
    return to_string(configJSON[ConfigConverterJSON::configStr][ConfigConverterJSON::nameStr]) + ", v." +
           to_string(configJSON[ConfigConverterJSON::configStr][ConfigConverterJSON::versionStr]);
}

JSON& ConverterJSON::getAnswersJSON()
{
    return answersJSON;
}

std::vector<std::string> ConverterJSON::getFilePaths()
{
    std::vector<std::string> filePaths(configJSON[ConfigConverterJSON::filesStr]);

    return filePaths;
}

int ConverterJSON::getMaxResponses()
{

    return configJSON[ConfigConverterJSON::configStr][ConfigConverterJSON::max_responsesStr];

}

std::vector<std::string> ConverterJSON::getRequests()
{
    std::vector<std::string> requests;

    for (auto& elem : static_cast<std::vector<std::string>>(requestsJSON[ConfigConverterJSON::requestsStr]))
    {
        requests.push_back(elem);
    }

    return requests;
}