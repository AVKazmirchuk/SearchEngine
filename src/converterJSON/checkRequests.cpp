//
// Created by Alexander on 31.03.2025.
//



#include "converterJSON.h"



void ConverterJSON::checkRequests()
{
    if (requestsJSON[constants::requestsStr].empty())
    {
        throw CheckFileException(ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY);
    }
}