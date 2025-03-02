#include <iostream>

#include "Initialization.h"
#include "exceptions.h"
#include "searchEngine.h"
#include "general.h"
#include <limits>



//Функция печати имён файлов
/*void printContainer(const std::list<std::pair<unsigned long, std::filesystem::path>>&& container)
{
    std::cout << '\n' << "Files:" << '\n';

    for (const auto& fsPath : container)
    {
        std::cout << fsPath.first << " - " << fsPath.second.filename() << '\n';
    }

    std::cout << '\n';
}*/

void pressAnyKey(const char* message)
{
    std::cout << "\n\n" << "***   " << message << "   ***" << "\n\n";

    // reset any error flags
    std::cin.clear();
    // ignore any characters in the input buffer until we find a newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // get one more char from the user (waits for user to press enter)
    std::cin.get();
}

int main()
{

    Initialization config{constants::configFilePath};

    try
    {
        config.openFile();
    }
    catch(const CheckFileException& e)
    {
        std::cout << '\n' << e.what() << '\n';
        return static_cast<int>(e.getErrorCode());
    }

    std::cout << config.about() << '\n';


    SearchEngine searchEngine;

    searchEngine.searchModifiedAll();

    /*pressAnyKey("searchModifiedAll");

    searchEngine.searchModifiedDocuments();

    pressAnyKey("searchModifiedDocuments");

    searchEngine.searchModifiedRequests();

    pressAnyKey("searchModifiedRequests");

    searchEngine.searchModifiedAll();

    pressAnyKey("searchModifiedAll");*/

    //std::cout << "std::thread::hardware_concurrency(): " << std::thread::hardware_concurrency();




































    //JSON-объекты
    /*nlohmann::json config = R"(
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

    nlohmann::json requests = R"(
{
  "requests": [
    "of the and water is year",
    "water another good see",
    "music"
  ]
}
)"_json;

    nlohmann::json answers = R"(
{
  "answers": {
    "request001": {
      "result": "true",
      "relevance": [
        "docid: 0, rank: 0.989",
        "docid: 1, rank: 0.897",
        "docid: 2, rank: 0.750",
        "docid: 3, rank: 0.670"
      ]
    },
    "request002": {
      "result": "true",
      "docid": 0, "rank": 0.769
    },
    "request003": {
      "result": "false"
    }
  }
}
)"_json;*/






    return 0;
}





