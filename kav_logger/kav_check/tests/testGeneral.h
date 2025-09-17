//
// Created by Alexander on 27.03.2025.
//



#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H

#include "operationFileAndJSON.h"



namespace testConstants
{
    //Путь файла конфигурации
    extern const std::string configFilePath;

    //JSON-шаблон файла конфигурации
    extern const kav::JSON configTemplate;

    //Несоответствующий структуре JSON-шаблон файла конфигурации
    extern const kav::JSON configNotMatchTemplate;

    //JSON-шаблон файла конфигурации с пустым массивом
    extern const kav::JSON configWrongTemplate;

    //Путь файла конфигурации с повреждённой структурой
    extern const std::string configNotValid;

    //Путь текстового файла
    extern const std::string fileText;

    //Имя поля массива
    extern const std::string files;

}

/*
 * Записать файлы для тестирования
 */
void putFiles();



#endif //SEARCH_ENGINE_TESTGENERAL_H
