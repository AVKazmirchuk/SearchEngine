//
// Created by Alexander on 08.03.2025.
//

#include <iostream>

#include "checkFile.h"


bool CheckFile::isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate)
{
    for (const auto &elemTemplate: objectJSONTemplate.items())
    {
        //Искать текущее поле шаблона в проверяемом
        const auto elem{objectJSON.find(elemTemplate.key())};

        //Поле шаблона не найдено в проверяемом
        if (elem == objectJSON.end())
        {
            //Выбросить исключение
            throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED);
        }

        //Типы значений полей шаблона и проверяемого не равны
        if (elem.value().type() != elemTemplate.value().type())
        {
            //Выбросить исключение
            throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED);
        }

        //Тип значения поля - JSON-объект, тогда функция вызывается рекурсивно с текущими аргументами зачений полей шаблона и проверяемого
        if (elemTemplate.value().is_object())
        {
            isJSONStructureMatchImpl(elem.value(), elemTemplate.value());
        }
    }

    return true;
}