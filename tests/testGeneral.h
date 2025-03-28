//
// Created by Alexander on 27.03.2025.
//

#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H



namespace testConstants
{

    extern const JSON configWrongTemplate;

    extern const JSON requestsWrongTemplate;

    extern const JSON configWrongArray;

    extern const std::vector<std::vector<std::pair<std::uint64_t , float>>> answers;

}

void putFiles();

void deleteFiles();


#endif //SEARCH_ENGINE_TESTGENERAL_H
