//
// Created by Alexander on 27.03.2025.
//

#include "general.h"
#include "testGeneral.h"



namespace testConstants
{

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

}
