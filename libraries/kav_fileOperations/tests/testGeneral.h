//
// Created by Alexander on 27.03.2025.
//



#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H

#include "operationFileAndJSON.h"

const JSON &Bases::requestsJSON()
{
    static const JSON varRequests= JSON::parse(R"(
    {
         "requests":
    [
    "susic",
    "water anothers gaad saa",
    "of the and water is year"

  ]
    }
    )");

    return varRequests;
}

/**
 * Класс хранения переменных программы
 */
class ProgramArguments
{

public:

    ProgramArguments() = delete;

    /**
     * Путь файла конфигурации
     * @return Ссылка на переменную
     */
    static const std::string& configFilePath()
    {
        //Значение по умолчанию
        static const std::string variable{"config.json"};
        return variable;
    }

    /**
     * Прочитать JSON-шаблон файла конфигурации
     * @return Ссылка на переменную
     */
    static const kav::JSON &configTemplate()
    {
        //Значение по умолчанию
        static const kav::JSON variable = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "1.0.0",
        "max_responses": 5
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
     ]
    }
    )");

        return variable;
    }

    /**
     * Прочитать несоответствующий структуре JSON-шаблон файла конфигурации
     * @return Ссылка на переменную
     */
    static const kav::JSON &configNotMatchTemplate()
    {
        //Значение по умолчанию
        static const kav::JSON variable = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1"
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
     ]
    }
    )");

        return variable;
    }

    /**
     * Прочитать JSON-шаблон файла конфигурации с пустым массивом
     * @return Ссылка на переменную
     */
    static const kav::JSON &configArrayEmptyTemplate()
    {
        //Значение по умолчанию
        static const kav::JSON variable = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
      },
     "files": [

     ]
    }
    )");

        return variable;
    }

};
namespace testConstants
{
    //Путь файла конфигурации
    //extern const std::string configFilePath;

    //JSON-шаблон файла конфигурации
    //extern const kav::JSON configTemplate;

    //Несоответствующий структуре JSON-шаблон файла конфигурации
    //extern const kav::JSON configNotMatchTemplate;

    //JSON-шаблон файла конфигурации с пустым массивом
    //extern const kav::JSON configArrayEmptyTemplate;

    //Путь файла конфигурации с повреждённой структурой
    extern const std::string configNotValid;

    //Путь текстового файла
    extern const std::string textFile;

    //Путь текстового файла со строками
    extern const std::string textFileMultylines;

    //Путь текстового файла для записи
    extern const std::string textFileForWrite;

    //Текстовая строка для записи
    extern const std::string textString;

    //Содержимое файла file001.txt
    extern const std::string fileContents;

    //Содержимое файла fileMultylines.txt (первая строка)
    extern const std::string fileFirstLineContents;

    //Содержимое файла fileMultylines.txt (последняя строка)
    extern const std::string fileLastLineContents;

    //Имя поля массива
    extern const std::string files;

}

/*
 * Записать файлы для тестирования
 */
void putFiles();



#endif //SEARCH_ENGINE_TESTGENERAL_H
