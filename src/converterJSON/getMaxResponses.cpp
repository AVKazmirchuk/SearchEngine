//
// Created by Alexander on 27.01.2025.
//

#include <iostream>

#include "converterJSON.h"
#include "general.h"



int ConverterJSON::getMaxResponses()
{

    return configJSON[constants::configStr][constants::max_responsesStr];

}