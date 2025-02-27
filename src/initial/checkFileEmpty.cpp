//
// Created by Alexander on 28.01.2025.
//



#include "initialize.h"



bool Initialize::checkFileEmpty()
{
    return objectJSON.contains("config");
}