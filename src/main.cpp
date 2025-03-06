#include <iostream>

#include "checkFile.h"
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

   /*
    //Проверить файл на существование
    if (!checkFileExists(fileName)) throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, configFilePath.string());
    //Проверка файла на неповреждённость JSON-структуры
    if (!checkJSONStructureValid()) throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, configFilePath.string());

    if (!checkFileEmpty()) throw CheckFileException(ErrorCode::ERROR_FILE_EMPTY, configFilePath.string());
    */


int main()
{

    CheckFile checkFile;

    //Проверить файл config.json на существование
    if (!checkFile.isExist(constants::configFilePath))
    {
        throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, constants::configFilePath);
    }

    //Проверить файл requests.json на существование
    if (!checkFile.isExist(constants::requestsFilePath))
    {
        throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, constants::requestsFilePath);
    }

    //Проверить файл config.json на целостность JSON-структуры
    if (!checkFile.isJSONStructureValid(constants::configFilePath))
    {
        CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, constants::configFilePath);
    }

    //Проверить файл requests.json на целостность JSON-структуры
    if (!checkFile.isJSONStructureValid(constants::requestsFilePath))
    {
        CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, constants::requestsFilePath);
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






    /*nlohmann::json answers = R"(
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





