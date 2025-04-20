//
// Created by Alexander on 31.03.2025.
//



#include "converterJSON.h"
#include "logger.h"


void ConverterJSON::checkRequests()
{
    if (requestsJSON[constants::requestsStr].empty())
    {
        Logger::fatal("void ConverterJSON::checkRequests()" ,CheckFileException(ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY));
        throw CheckFileException(ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY);
    }
}