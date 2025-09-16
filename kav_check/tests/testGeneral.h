//
// Created by Alexander on 27.03.2025.
//



#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H

#include "operationFileAndJSON.h"



namespace testConstants
{
    extern const kav::JSON configTemplate;

    extern const kav::JSON configNotMatchTemplate;

    extern const kav::JSON requestsTemplate;

    extern const kav::JSON configWrongTemplate;

    extern const kav::JSON requestsWrongTemplate;

    extern const kav::JSON configWrongArray;

    extern const std::vector<std::vector<std::pair<std::uint64_t , float>>> answers;

    extern const kav::JSON answersTest;

}

/*
 * Записать файлы для тестирования
 */
void putFiles();

/*
 * Удалить файлы для тестирования
 */
void deleteFiles();

//Константы переменных
namespace constants
{

    //Путь файла конфигурации
    extern const std::string configFilePath;
    //Путь файла запросов
    extern const std::string requestsFilePath;
    //Путь файла ответов
    extern const std::string answersFilePath;

    extern const std::string configNotValid;

    extern const std::string fileText;

    //Путь файла конфигурации логирования
    extern const std::string configLoggerFilePath;
    //Путь файла конфигурации очереди сообщений
    extern const std::string configWriterMessageFilePath;

    //Количество знаков после запятой
    extern const int precision;
    //Ширина вывода
    extern const int formatByWidth;

}

#endif //SEARCH_ENGINE_TESTGENERAL_H
