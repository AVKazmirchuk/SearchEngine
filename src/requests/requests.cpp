//
// Created by Alexander on 08.01.2026.
//



#include "requests.h"



void Requests::updateRequests(const std::vector<std::string>& in_requests)
{
    requests = in_requests;
}

void Requests::updateRequests(std::vector<std::string>&& in_requests)
{
    requests = std::move(in_requests);
}

const std::vector<std::string>& Requests::getRequests()
{
    return requests;
}

void Requests::clearRequests()
{
    requests.clear();
}
