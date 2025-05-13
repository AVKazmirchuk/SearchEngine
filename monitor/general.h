//
// Created by Alexander on 07.05.2025.
//

#ifndef SEARCH_ENGINE_GENERAL_H
#define SEARCH_ENGINE_GENERAL_H


#include <list>
#include <string>

#include "nlohmann/json.hpp"



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

    //Путь файла конфигурации логирования
    extern const std::string configMessageQueueFilePath;

}



#endif //SEARCH_ENGINE_GENERAL_H
