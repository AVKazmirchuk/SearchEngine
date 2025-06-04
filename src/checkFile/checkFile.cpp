//
// Created by Alexander on 31.03.2025.
//



#include "fileOperation.h"
//#include "logger.h"



bool CheckJSON::isJSONStructureValid(std::ifstream& inFile)
{
    //Создать временный объект для проверки
    JSON tmpJSON;

    try
    {
        //Прочитать JSON-структуру
        inFile >> tmpJSON;
        inFile.clear();
        inFile.seekg(0);
    }
    catch (const nlohmann::detail::parse_error &e)
    {
        //JSON-структура повреждена
        return false;
    }

    //JSON-структура целостна
    return true;
}

bool CheckJSON::isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate)
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
            throw std::runtime_error("error_json_structure_not_match");
        }

        //Типы значений полей шаблона и проверяемого не равны
        if (elem.value().type() != elemTemplate.value().type())
        {
            //Выбросить исключение
            throw std::runtime_error("error_json_structure_not_match");
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

bool CheckJSON::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate)
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




