//
// Created by Alexander on 27.03.2025.
//


#include "testGeneral.h"



namespace testConstants {

    const std::string configFilePath{"config.json"};

    const std::string configNotValid{"configNotValid.json"};

    const std::string fileText{"file001.txt"};

    const std::string files{"files"};

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

    const kav::JSON configNotMatchTemplate = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1"
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
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

}

void putFiles()
{
    std::filesystem::remove("config.json");
    std::filesystem::remove("configNotValid.json");
    //std::filesystem::remove("configNotMatch.json");
    std::filesystem::remove("file001.txt");
    std::filesystem::remove("connectDisk.bat");
    std::filesystem::remove("disconnectDisk.bat");

    //std::filesystem::remove_all("resources");

    std::filesystem::copy("../../tests/resources/config.json", "config.json");
    std::filesystem::copy("../../tests/resources/configNotValid.json", "configNotValid.json");
    //std::filesystem::copy("../../tests/resources/configNotMatch.json", "configNotMatch.json");
    std::filesystem::copy("../../tests/resources/file001.txt", "file001.txt");
    std::filesystem::copy("../../tests/resources/connectDisk.bat", "connectDisk.bat");
    std::filesystem::copy("../../tests/resources/disconnectDisk.bat", "disconnectDisk.bat");

    //std::filesystem::copy("../../tests/resources/resources", "resources");
}

