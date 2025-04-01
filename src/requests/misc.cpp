//
// Created by Alexander on 31.03.2025.
//



#include "requests.h"



const std::vector<std::string>& Requests::getRequests()
{
    return requests;
}

void Requests::clearRequests()
{
    requests.clear();
}
