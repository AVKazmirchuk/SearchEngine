//
// Created by Alexander on 08.03.2025.
//

#include <iostream>

#include "checkFile.h"
#include <exception>
#include <stdexcept>



bool CheckFile::isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate)
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
            throw std::runtime_error("ERROR_FILE_STRUCTURE_NOT_MATCH");
        }

        //Типы значений полей шаблона и проверяемого не равны
        if (elem.value().type() != elemTemplate.value().type())
        {
            //Выбросить исключение
            throw std::runtime_error("ERROR_FILE_STRUCTURE_NOT_MATCH");
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
