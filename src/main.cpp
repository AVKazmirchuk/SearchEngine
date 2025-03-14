#include <iostream>

#include "checkFile.h"
#include "exceptions.h"
#include "searchEngine.h"
#include "general.h"
#include "logger.h"
#include <limits>

#include "gtest/gtest.h"

void pressAnyKey(const char* message)
{
    Logger().info("***   " + std::string(message) + "   ***");

    // reset any error flags
    std::cin.clear();
    // ignore any characters in the input buffer until we find a newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // get one more char from the user (waits for user to press enter)
    std::cin.get();
}

   
   void checkFile(const std::string& filePath, const JSON &objectJSONTemplate)
   {
       //Проверить файл на существование
       if (!CheckFile().isExist(filePath))
       {
           Logger().fatal("File " + std::string(filePath) + " is missing!");
           throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath);
       }

       //Другие проверки файла...
       //Проверить файл на целостность JSON-структуры
       if (!CheckFile().isJSONStructureValid(filePath))
       {
           throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, filePath);
       }

       //Проверить JSON-структуру файла на соответствие шаблону
       if (!CheckFile().isJSONStructureMatch( ReadWriteJSONFile().readJSONFile(filePath), objectJSONTemplate))
       {
           throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH, filePath);
       }
   }

int main()
{



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





