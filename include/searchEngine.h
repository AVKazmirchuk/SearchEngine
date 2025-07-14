//
// Created by Alexander on 18.02.2025.
//

#ifndef SEARCH_ENGINE_SEARCHENGINE_H
#define SEARCH_ENGINE_SEARCHENGINE_H



#include <cstdint>



#include "converterJSON.h"
#include "documents.h"
#include "invertedIndex.h"
#include "requests.h"
#include "relevantResponse.h"
#include "readTextFile.h"
#include "kav/operationFileAndJSON.h"
#include "general.h"
#include "kav/logger/logger.h"







/**
 * Класс организует взаимодействие между другими классами
 */
class SearchEngine
{

public:

    SearchEngine(const std::string& in_configFilePath, const std::string& in_requestsFilePath)
    : configSearchEngine(in_configFilePath, in_requestsFilePath),

      converterJSONObj(configSearchEngine.getConfigJSON(), configSearchEngine.getRequestsJSON()),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())

    {
        kav::Logger::info(converterJSONObj.about());
    }

    /**
     * Инициализирует объекты классов
     * @param in_configJSON
     * @param in_requestsJSON
     */
    /*SearchEngine(const JSON& in_configJSON, const JSON& in_requestsJSON)

    : converterJSONObj(in_configJSON, in_requestsJSON),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())

    {
        Logger::info(converterJSONObj.about());
    }*/

    /**
     * Инициализирует объекты классов
     * @param in_configJSON
     * @param in_requestsJSON
     */
    /*SearchEngine(JSON&& in_configJSON, JSON&& in_requestsJSON)

    : converterJSONObj(std::move(in_configJSON), std::move(in_requestsJSON)),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())

    {
        Logger::info(converterJSONObj.about());
    }*/

    /**
     * Рассчитать релевантность ответов
     */
    void searchModifiedAll();

    /**
     * Рассчитать релевантность ответов, при изменении документов
     */
    void searchModifiedDocuments();

    /**
     * Рассчитать релевантность ответов, при изменении запросов
     */
    void searchModifiedRequests();

    /**
     * Преобразовать базу релевантности ответов в другой тип
     * @return Преобразованная база релевантности ответов
     */
    std::vector<std::vector<std::pair<std::uint64_t, float>>> exportRelevantResponses();

private:

    /**
     * Класс реализует чтение и хранение параметров для настройки класса SearchEngine
     */
    class ConfigSearchEngine
    {

    public:

        explicit ConfigSearchEngine(const std::string& in_configFilePath, const std::string& in_requestsFilePath)
        : configFilePath{in_configFilePath}, requestsFilePath{in_requestsFilePath}
        {
            initialize();
        }

        [[nodiscard]] JSON getConfigJSON() const {return configJSON;}
        [[nodiscard]] JSON getRequestsJSON() const {return requestsJSON;}




    private:

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

        //Путь файла конфигурации логирования
        std::string configFilePath;
        std::string requestsFilePath;
        //JSON-объект конфигурации логирования
        JSON configJSON;
        JSON requestsJSON;

        /**
         * Инициализировать (настроить) класс
         */
        void initialize();

    };

    //Объект чтения и хранения параметров для настройки класса Logger
    ConfigSearchEngine configSearchEngine;

    JSON configJSON;
    JSON requestsJSON;

    /**
     * JSON-объекты
     */
    ConverterJSON converterJSONObj;

    /**
     * Документы
     */
    Documents documentsObj;

    /**
     * Инвертированный индекс
     */
    InvertedIndex invertedIndexObj;

    /**
     * Запросы
     */
    Requests requestsObj;

    /**
     * Релевантные ответы
     */
    RelevantResponse relevantResponseObj;

    /**
     * Записать в JSON-файл результаты поиска
     * @param objectJSON
     * @param filePath
     */
    void writeAnswersToFile(const JSON& objectJSON, const std::string& filePath);

    std::vector<std::string> readDocsFromFiles(const std::vector<std::string>& filePaths);

};



#endif //SEARCH_ENGINE_SEARCHENGINE_H
