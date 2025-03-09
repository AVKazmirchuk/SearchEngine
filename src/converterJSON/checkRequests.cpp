//
// Created by Alexander on 08.03.2025.
//



#include "converterJSON.h"
#include "exceptions.h"



void ConverterJSON::checkRequests()
{
    if (requestsJSON[constants::requestsStr].empty())
    {
        Logger().fatal("The query array is empty!");
        throw CheckFileException(ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY);
    }
}