//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_GENERAL_H
#define SEARCH_ENGINE_GENERAL_H



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

    //Путь файла конфигурации логирования
    extern const std::string configLoggerFilePath;
    //Путь файла конфигурации очереди сообщений
    extern const std::string configWriterMessageFilePath;

    //Количество знаков после запятой
    extern const int precision;
    //Ширина вывода
    extern const int formatByWidth;

}

/**
 * Выйти из программы
 */
void exitProgram();



#endif //SEARCH_ENGINE_GENERAL_H
