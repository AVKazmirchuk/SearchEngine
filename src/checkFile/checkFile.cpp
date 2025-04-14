//
// Created by Alexander on 31.03.2025.
//



#include "checkFile.h"



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

bool CheckFile::isJSONStructureValid(const std::string &fileName)
{
    //Создать объект для проверки файла
    std::ifstream inFile(fileName);

    //Проверить файл на открытие для чтения
    if (!inFile.is_open())
    {
        throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, fileName);
    }

    //Создать временный объект для поверки
    JSON tmpJSON;

    try
    {
        //Прочитать JSON-структуру
        inFile >> tmpJSON;
    }
    catch (const nlohmann::detail::parse_error &e)
    {
        inFile.close();
        //JSON-структура повреждена
        return false;
    }

    inFile.close();
    //JSON-структура целостна
    return true;
}

