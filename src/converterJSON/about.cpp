//
// Created by Alexander on 06.03.2025.
//



#include "converterJSON.h"



std::string ConverterJSON::about()
{
    return to_string(configJSON[constants::configStr][constants::nameStr]) + ", v." +
           to_string(configJSON[constants::configStr][constants::versionStr]);
}