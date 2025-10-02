//
// Created by Alexander on 27.03.2025.
//

#include "types.h"
#include "testGeneral.h"



namespace testConstants {

    const JSON configTemplate = JSON::parse(R"(
    {
  "config": {
    "name": "SkillboxSearchEngine",
    "version": "1.0.0",
    "max_responses": 5
  },
  "files": [
    "resources/file001.txt",
    "resources/file002.txt",
    "resources/file003.txt"
  ]
}
    )");

    const JSON requestsTemplate = JSON::parse(R"(
    {
  "requests": [
    "of the and water is year",
    "water another good see",
    "music"
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

    const JSON answersTest = JSON::parse(R"(
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

