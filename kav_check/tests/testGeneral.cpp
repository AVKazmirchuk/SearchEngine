//
// Created by Alexander on 27.03.2025.
//

//#include "general.h"
#include "testGeneral.h"



namespace testConstants {

    const kav::JSON configTemplate = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
     ]
    }
    )");

    const kav::JSON requestsTemplate = kav::JSON::parse(R"(
    {
      "requests": [
        "of the and water is year",
        "water another good see",
        "music"
      ]
    }
    )");

    const kav::JSON configWrongTemplate = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
      },
     "files": [

     ]
    }
    )");

    const kav::JSON requestsWrongTemplate = kav::JSON::parse(R"(
    {
      "requests": [

      ]
    }
    )");

    const kav::JSON configWrongArray = kav::JSON::parse(R"(
    {
        "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
    },
    "files": [
    "resources/file001.txt",
    "resources/file999.txt",
    "resources/file003.txt"
    ]
    }
    )");

    const std::vector<std::vector<std::pair<std::uint64_t , float>>> answers =
            {
                    {
                        {0, 1.0}, {2, 0.947368}, {1, 0.77193}
                    },
                    {
                            {0, 0.017544}
                    },
                    {

                    }
            };

    const kav::JSON answersTest = kav::JSON::parse(R"(
    {
        "answers": {
            "request001": {
                "result": "true",
                "relevance": [
                {
                    "docid": 0,
                    "rank": 1.0
                },
                {
                    "docid": 2,
                    "rank": 0.947368
                },
                {
                    "docid": 1,
                    "rank": 0.77193
                }
            ]
                },
            "request002": {
                "result": "true",
                "docid": 0,
                "rank": 0.017544
                },
           "request003": {
               "result": "false"
           }
        }
    }
    )");

}

void putFiles()
{
    std::filesystem::remove("config.json");
    std::filesystem::remove("configNotValid.json");
    std::filesystem::remove("configNotMatch.json");
    std::filesystem::remove("requests.json");
    std::filesystem::remove("answers.json");


    std::filesystem::remove_all("resources");


    std::filesystem::copy("../../tests/resources/config.json", "config.json");
    std::filesystem::copy("../../tests/resources/configNotValid.json", "configNotValid.json");
    std::filesystem::copy("../../tests/resources/configNotMatch.json", "configNotMatch.json");
    std::filesystem::copy("../../tests/resources/requests.json", "requests.json");
    std::filesystem::copy("../../tests/resources/answers.json", "answers.json");

    std::filesystem::copy("../../tests/resources/resources", "resources");
}

void deleteFiles()
{
    std::filesystem::remove("configNotValid.json");
    std::filesystem::remove("configNotMatch.json");
}

namespace constants
{

    const std::string configFilePath{"config.json"};
    const std::string requestsFilePath{"requests.json"};
    const std::string answersFilePath{"answers.json"};
    const std::string configLoggerFilePath{"logger.json"};
    const std::string configWriterMessageFilePath{"messageQueue.json"};

    const int precision{6};
    const int formatByWidth{2};

}