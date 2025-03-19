//
// Created by Alexander on 05.03.2025.
//

#include <iostream>

#include "checkFile.h"
#include <exception>
#include <stdexcept>



bool CheckFile::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate)
{
    try
    {
        //Проверить JSON-структуру файла на соответствие шаблону
        isJSONStructureMatchImpl(objectJSON, objectJSONTemplate);
    }
    catch(const std::runtime_error& e)
    {
        //JSON-структура файла не соответствует шаблону
        return false;
    }

    //JSON-структура файла соответствует шаблону
    return true;
}
