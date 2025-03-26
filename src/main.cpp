#include <iostream>

#include "checkFile.h"
#include "checkFileException.h"
#include "searchEngine.h"
#include "general.h"
#include "logger.h"





int main()
{

    //std::atexit(pressAnyKey);

    //Проверить файл config.json
    checkFile(constants::configFilePath, constants::configTemplate);
    //Проверить файл requests.json
    checkFile(constants::requestsFilePath, constants::requestsTemplate);

    SearchEngine searchEngine(ReadWriteJSONFile().readJSONFile(constants::configFilePath),
                              ReadWriteJSONFile().readJSONFile(constants::requestsFilePath));

    searchEngine.searchModifiedAll();

    /*pressAnyKey("searchModifiedAll");

    searchEngine.searchModifiedDocuments();

    pressAnyKey("searchModifiedDocuments");

    searchEngine.searchModifiedRequests();

    pressAnyKey("searchModifiedRequests");

    searchEngine.searchModifiedAll();

    pressAnyKey("searchModifiedAll");*/

    //std::cout << "std::thread::hardware_concurrency(): " << std::thread::hardware_concurrency();

    return 0;
}





