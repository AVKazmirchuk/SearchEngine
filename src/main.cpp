#include <iostream>

#include "initialize.h"
#include "exceptions.h"
#include "converterJSON.h"
#include "documents.h"
#include "invertedIndex.h"
#include "requests.h"
#include "relevantResponse.h"
#include "relativeIndex.h"
#include "searchEngine.h"
#include <limits>

namespace constants
{
    extern const char *configFilePath;
    extern const char *requestsFilePath;
    extern const char *answersFilePath;
}

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

    Initialize config{static_cast<const std::string>(constants::configFilePath)};

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


    /*
    //ПОРЯДОК СОЗДАНИЯ ОБЪЕКТОВ КЛАССОВ ДЛЯ ПОЛУЧЕНИЯ РЕЛЕВАНТНЫХ ОТВЕТОВ ПО ЗАПРОСАМ
    //------------------------------
    //Конструировать объект для работы с JSON-файлами
    ConverterJSON converterJson;

    //Конструировать объект для загрузки и хранения списка документов
    Documents documents;

    //Обновить список документов из файлов
    documents.updateDocuments(converterJson.getDocuments());

    //Конструировать объект для получения инвертированной индексации документов
    InvertedIndex invertedIndex(documents.getDocuments());



    std::cin.clear(); // reset any error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
    std::cin.get(); // get one more char from the user (waits for user to press enter)



    //Обновить базу инвертированного индекса
    invertedIndex.updateFrequencyDictionary();



    std::cout << "\nSize Of InvertedIndex: " << sizeof(invertedIndex) << '\n';
    std::cin.clear(); // reset any error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
    std::cin.get(); // get one more char from the user (waits for user to press enter)



    //Конструировать объект для загрузки и хранения списка запросов
    Requests requests;

    //Обновить список запросов из файла
    requests.updateRequests(converterJson.getRequests());

    //Конструировать объект для определения релевантности поисковых запросов
    SearchServer relevantResponse(invertedIndex.getFrequencyDictionary(),
                           requests.getRequests());



    std::cin.clear(); // reset any error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any characters in the input buffer until we find a newline
    std::cin.get(); // get one more char from the user (waits for user to press enter)
    std::cout << "\nSize Of SearchServer: " << sizeof(relevantResponse) << '\n';



    //Рассчитать релевантность ответов
    relevantResponse.updateRelevantResponses();

    //ПРЕОБРАЗОВАНИЕ БАЗЫ РЕЛЕВАНТНЫХ ОТВЕТОВ В ДРУГОЙ ТИП
    //------------------------------
    auto answersTmp{relevantResponse.getRelevantResponses()};

    std::vector<std::vector<std::pair<int, float>>> answers;

    //Преобразование из типа std::vector<std::vector<RelativeIndex>> в тип std::vector<std::vector<std::pair<int, float>>>
    std::size_t requestId{};
    for (auto& request : answersTmp)
    {
        answers.emplace_back(std::vector<std::pair<int, float>>{});
        for (auto& relativeIndex : request)
        {
            answers[requestId].emplace_back(relativeIndex.doc_id, relativeIndex.rank);
        }
        ++requestId;
    }
    //------------------------------

    //Записывает в файл answers.json результаты поиска, с учётом максимального количества ответов
    converterJson.putAnswers(answers, converterJson.getMaxResponses());
    //------------------------------
    */




























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





