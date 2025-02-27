//
// Created by Alexander on 15.02.2025.
//



#include "requests.h"



void Requests::updateRequests(std::vector<std::string> in_requests)
{
    for (auto& elem : in_requests)
    {
        requests.emplace_back(std::move(characterToLower(elem)));
    }
}