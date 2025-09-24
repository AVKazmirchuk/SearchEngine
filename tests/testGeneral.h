//
// Created by Alexander on 27.03.2025.
//

#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H



#include "nlohmann/json.hpp"

#include "types.h"


namespace testConstants
{

    extern const JSON configTemplate;

    extern const JSON requestsTemplate;

    extern const std::vector<std::vector<std::pair<std::uint64_t , float>>> answers;

    extern const JSON answersTest;

}

void putFiles();

void deleteFiles();


#endif //SEARCH_ENGINE_TESTGENERAL_H
