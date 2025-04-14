//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_GENERAL_H
#define SEARCH_ENGINE_GENERAL_H



//#include <cstdlib>
//#include <iostream>

#include "windows.h"
#include "nlohmann/json.hpp"

#include "checkFileException.h"



//Тип объектов заменён на nlohmann::ordered_json (сохраняет порядок вставки)
//Тип для чисел с плавающей запятой заменён на float
using JSON = nlohmann::basic_json<
        nlohmann::ordered_map,
        std::vector,
        std::string,
        bool,
        std::int64_t,
        std::uint64_t,
        float>;

//Константы переменных
namespace constants
{

    //Путь файла конфигурации
    extern const std::string configFilePath;
    //Путь файла запросов
    extern const std::string requestsFilePath;
    //Путь файла ответов
    extern const std::string answersFilePath;

    //Имя поля "config" файла конфигурации
    extern const std::string configStr;
    //Имя поля "name" файла конфигурации
    extern const std::string nameStr;
    //Имя поля "version" файла конфигурации
    extern const std::string versionStr;
    //Имя поля "max_responses" файла конфигурации
    extern const std::string max_responsesStr;
    //Имя поля "files" файла конфигурации
    extern const std::string filesStr;

    //Имя поля "requests" файла запросов
    extern const std::string requestsStr;

    //Имя поля "answers" файла ответов
    extern const std::string answersStr;
    //Имя поля "request" файла ответов
    extern const std::string requestStr;
    //Имя поля "result" файла ответов
    extern const std::string resultStr;
    //Значение "true" поля "result" файла ответов
    extern const std::string trueStr;
    //Значение "false" поля "result" файла ответов
    extern const std::string falseStr;
    //Имя поля "relevance" файла ответов
    extern const std::string relevanceStr;
    //Имя поля "docid" файла ответов
    extern const std::string docIdStr;
    //Имя поля "rank" файла ответов
    extern const std::string rankStr;

    //Количество знаков после запятой
    extern const int precision;
    //Ширина вывода
    extern const int formatByWidth;

    //JSON-объект файла config.json
    extern const JSON configTemplate;

    //JSON-объект файла requests.json
    extern const JSON requestsTemplate;

    extern const std::string configLoggerFilePath;

}

/**
 * Выйти из программы
 */
void exitProgram();

/**
 * Проверить последовательно файл на существование, на возможность открытия для чтения, на целостность JSON-структуры, на соответствие шаблону
 * @param filePath Имя файла
 * @param objectJSONTemplate Шаблон JSON-объекта
 */
void checkFile(const std::string& filePath, const JSON &objectJSONTemplate);

/**
 * Запустить независимый процесс получения и вывода сообщений
 * @param lpApplicationName Имя процесса
 */
void startMonitor(LPCSTR lpApplicationName);

/**
 * Отправить сообщение другому независимому процессу
 * @param message Сообщение
 */
void sendMessage(const std::string& message);

/**
 * Определить, запущен ли процесс
 * @param processName Имя процесса
 * @return Процесс запущен (true)/не запущен (false)
 */
bool isProcessRun(const char * const processName);

#endif //SEARCH_ENGINE_GENERAL_H
