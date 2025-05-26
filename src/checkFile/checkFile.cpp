//
// Created by Alexander on 31.03.2025.
//



#include "checkFile.h"
#include "logger.h"

bool CheckFile::isJSONStructureValid(std::ifstream& inFile)
{
    //isFileOpenRead(inFile, filePath, message);

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
        //Logger::error(message);

        return false;
    }

    //JSON-структура целостна
    return true;
}

void CheckFile::isJSONStructureValid(std::ifstream& inFile, const std::string& filePath, const std::string& message, const std::exception&)
{
    isFileOpenRead(inFile, filePath, message, std::runtime_error("e"));

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
        Logger::fatal(message, CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, filePath));
        throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, filePath);
    }
}

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

bool CheckFile::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate, const std::string& filePath, const std::string& message)
{
    try
    {
        //Проверить JSON-структуру файла на соответствие шаблону
        isJSONStructureMatchImpl(objectJSON, objectJSONTemplate);
    }
    catch(const std::runtime_error& e)
    {
        //JSON-структура файла не соответствует шаблону
        Logger::error(message);

        return false;
    }

    //JSON-структура файла соответствует шаблону
    return true;
}

void CheckFile::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate, const std::string& filePath, const std::string& message, const std::exception&)
{
    try
    {
        //Проверить JSON-структуру файла на соответствие шаблону
        isJSONStructureMatchImpl(objectJSON, objectJSONTemplate);
    }
    catch(const std::runtime_error& e)
    {
        //JSON-структура файла не соответствует шаблону
        Logger::fatal(message, CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH, filePath));
        throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH, filePath);
    }
}


