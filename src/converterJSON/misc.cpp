//
// Created by Alexander on 31.03.2025.
//



#include "converterJSON.h"



std::string ConverterJSON::about()
{
    //Вернуть строку о программе (название, версия)
    return to_string(configJSON[constants::configStr][constants::nameStr]) + ", v." +
           to_string(configJSON[constants::configStr][constants::versionStr]);
}

JSON& ConverterJSON::getAnswersJSON()
{
    return answersJSON;
}

std::vector<std::string> ConverterJSON::getFilePaths()
{
    std::vector<std::string> filePaths(configJSON[constants::filesStr]);

    return filePaths;
}

int ConverterJSON::getMaxResponses()
{

    return configJSON[constants::configStr][constants::max_responsesStr];

}

std::vector<std::string> ConverterJSON::getRequests()
{
    std::vector<std::string> requests;

    for (auto& elem : static_cast<std::vector<std::string>>(requestsJSON[constants::requestsStr]))
    {
        requests.push_back(elem);
    }

    return requests;
}