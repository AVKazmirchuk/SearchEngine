//
// Created by Alexander on 31.03.2025.
//



#include "general.h"
#include "checkFile.h"
#include "readWriteJSONFile.h"
#include "logger.h"



void exitProgram()
{
    std::exit(EXIT_FAILURE);
}



namespace constants
{

    const std::string configFilePath{"config.json"};
    const std::string requestsFilePath{"requests.json"};
    const std::string answersFilePath{"answers.json"};

    const std::string configStr{"config"};
    const std::string nameStr{"name"};
    const std::string versionStr{"version"};
    const std::string max_responsesStr{"max_responses"};
    const std::string filesStr{"files"};

    const std::string requestsStr{"requests"};

    const std::string answersStr{"answers"};
    const std::string requestStr{"request"};
    const std::string resultStr{"result"};
    const std::string trueStr{"true"};
    const std::string falseStr{"false"};
    const std::string relevanceStr{"relevance"};
    const std::string docIdStr{"docid"};
    const std::string rankStr{"rank"};

    const int precision{6};
    const int formatByWidth{2};

    const JSON configTemplate = JSON::parse(R"(
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

    const JSON requestsTemplate = JSON::parse(R"(
    {
      "requests": [
        "of the and water is year",
        "water another good see",
        "music"
      ]
    }
    )");

    const std::string configLoggerFilePath{"logger.json"};
    const std::string configWriterMessageFilePath{"messageQueue.json"};

}

