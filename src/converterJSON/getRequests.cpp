//
// Created by Alexander on 27.01.2025.
//



#include "converterJSON.h"
#include "general.h"



std::vector<std::string> ConverterJSON::getRequests()
{
    std::vector<std::string> requests;

    for (auto& elem : static_cast<std::vector<std::string>>(requestsJSON[constants::requestsStr]))
    {
        requests.push_back(elem);
    }

    return requests;
}