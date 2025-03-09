//
// Created by Alexander on 05.03.2025.
//

#include <iostream>

#include "checkFile.h"



bool CheckFile::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate)
{
    try
    {
        isJSONStructureMatchImpl(objectJSON, objectJSONTemplate);
    }
    catch(const CheckFileException& e)
    {
        return false;
    }

    return true;
}