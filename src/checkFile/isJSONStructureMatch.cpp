//
// Created by Alexander on 05.03.2025.
//

#include <iostream>

#include "checkFile.h"



bool CheckFile::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate)
{

    //std::cout << objectJSON << '\n';
    //std::cout << objectJSONTemplate << "\n\n\n";

    //auto elem = objectJSON.begin();

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