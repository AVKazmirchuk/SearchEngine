//
// Created by Alexander on 26.02.2025.
//



#include "converterJSON.h"



std::string ConverterJSON::convertIdtoStr(std::size_t requestId, std::string str)
{
    //В зависимости от разрядности ID запроса добавить нули
    if ((requestId + 1) / 10 < 1) str.append("00" + std::to_string(++requestId));
    else if ((requestId + 1) / 100 < 1) str.append("0" + std::to_string(++requestId));
    else if ((requestId + 1) / 1000 < 1) str.append(std::to_string(++requestId));

    return str;
}