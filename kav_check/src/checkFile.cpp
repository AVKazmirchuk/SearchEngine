//
// Created by Alexander on 31.03.2025.
//



#include "../include/kav/operationFileAndJSON.h"
#include "types.h"


bool kav::CheckJSON::isJSONStructureMatchImpl(const kav::JSON &objectJSON, const kav::JSON &objectJSONTemplate)
{
    //Для каждого поля JSON-объекта шаблона
    for (const auto &elemTemplate: objectJSONTemplate.items())
    {
        //Искать текущее поле шаблона в проверяемом
        const auto elem{objectJSON.find(elemTemplate.key())};

        //Поле шаблона не найдено в проверяемом
        if (elem == objectJSON.end())
        {
            //Выбросить исключение
            throw JSONStructureNotMatch{};
        }

        //Типы значений полей шаблона и проверяемого не равны
        if (elem.value().type() != elemTemplate.value().type())
        {
            //Выбросить исключение
            throw JSONStructureNotMatch{};
        }

        //Тип значения поля - JSON-объект
        if (elemTemplate.value().is_object())
        {
            //Проверить JSON-структуру файла на соответствие шаблону. Рекурсивный вызов
            isJSONStructureMatchImpl(elem.value(), elemTemplate.value());
        }
    }

    //JSON-структура файла соответствует шаблону
    return true;
}

bool kav::CheckJSON::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate)
{
    try
    {
        //Проверить JSON-структуру файла на соответствие шаблону
        isJSONStructureMatchImpl(objectJSON, objectJSONTemplate);
    }
    catch(const JSONStructureNotMatch&)
    {
        //JSON-структура файла не соответствует шаблону
        return false;
    }

    //JSON-структура файла соответствует шаблону
    return true;
}




