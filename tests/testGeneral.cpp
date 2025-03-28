//
// Created by Alexander on 27.03.2025.
//

#include "general.h"
#include "testGeneral.h"



namespace testConstants {

    const JSON configWrongTemplate = R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
      },
     "files": [

     ]
    }
    )"_json;

    const JSON requestsWrongTemplate = R"(
    {
      "requests": [

      ]
    }
    )"_json;

    const JSON configWrongArray = R"(
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
    )"_json;

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

}

void putFiles()
{
    std::filesystem::remove("config.json");
    std::filesystem::remove("configNotValid.json");
    std::filesystem::remove("configNotMatch.json");
    std::filesystem::remove("requests.json");
    std::filesystem::remove("answers.json");

    std::filesystem::remove("resources");

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
