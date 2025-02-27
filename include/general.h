//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_GENERAL_H
#define SEARCH_ENGINE_GENERAL_H



#include "nlohmann/json.hpp"



using ordered_float_json = nlohmann::basic_json<
        nlohmann::ordered_map,
        std::vector,
        std::string,
        bool,
        std::int64_t,
        std::uint64_t,
        float>;

namespace constants {
    extern const int precision;
    extern const int formatByWidth;

    extern const char *configFilePath;
    extern const char *requestsFilePath;
    extern const char *answersFilePath;

    extern const std::string answersStr;
    extern const std::string requestStr;
    extern const std::string filesStr;
    extern const std::string configStr;
    extern const std::string max_responsesStr;
    extern const std::string requestsStr;
    extern const std::string resultStr;
    extern const std::string falseStr;
    extern const std::string trueStr;
    extern const std::string relevanceStr;
    extern const std::string docIdStr;
    extern const std::string rankStr;
}

void exitProgram(const char* error);

#endif //SEARCH_ENGINE_GENERAL_H
