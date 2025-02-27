//
// Created by Alexander on 28.01.2025.
//



#include "nlohmann/json.hpp"

#include "general.h"



namespace constants
{
    const int precision{5};
    const int formatByWidth{2};

    const char *configFilePath{"../../config.json"};
    const char *requestsFilePath{"../../requests.json"};
    const char *answersFilePath{"../../answers.json"};

    const std::string answersStr{"answers"};
    const std::string requestStr{"request"};
    const std::string filesStr{"files"};
    const std::string configStr{"config"};
    const std::string max_responsesStr{"max_responses"};
    const std::string requestsStr{"requests"};
    const std::string resultStr{"result"};
    const std::string falseStr{"false"};
    const std::string trueStr{"true"};
    const std::string relevanceStr{"relevance"};
    const std::string docIdStr{"docid"};
    const std::string rankStr{"rank"};

/*
    //JSON-объекты
    nlohmann::json configJSON = R"(
{
"config": {
"name": "SkillboxSearchEngine",
"version": "0.1",
"max_responses": 5
},
"files": [
"../resources/file001.txt",
"../resources/file002.txt",
"../resources/file003.txt"
]
}
)"_json;

    nlohmann::json requestsJSON = R"(
{
"requests": [
"of the and water is year",
"water another good see",
"music"
]
}
)"_json;

    nlohmann::json answersJSON = R"(
{
"answers": {
"request001": {
  "result": "true",
  "relevance": [
  ]
}
}
}
)"_json;
 */
}

