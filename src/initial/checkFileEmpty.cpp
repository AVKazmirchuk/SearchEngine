//
// Created by Alexander on 28.01.2025.
//



#include "Initialization.h"



bool Initialization::checkFileEmpty()
{
    return objectJSON.contains("config");
}