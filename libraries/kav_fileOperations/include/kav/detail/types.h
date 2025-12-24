//
// Created by Alexander on 15.06.2025.
//

#ifndef kav_fileOperations_TYPES_H
#define kav_fileOperations_TYPES_H



#include "nlohmann/json.hpp"



namespace kav
{

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

}



#endif //kav_fileOperations_TYPES_H
