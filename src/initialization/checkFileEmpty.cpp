//
// Created by Alexander on 28.01.2025.
//



#include "Initialization.h"
#include "general.h"



bool initialization::checkFileEmpty()
{
    return objectJSON.contains(constants::configStr);
}