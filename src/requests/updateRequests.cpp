//
// Created by Alexander on 15.02.2025.
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