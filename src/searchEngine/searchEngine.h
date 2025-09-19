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
#include "kav/operationFileAndJSON.h"
#include "general.h"
#include "kav/logger.h"



/**
 * Класс организует взаимодействие между другими классами
 */
class SearchEngine
{

public:

    /**
     * Инициализирует объекты классов
     * @param in_configFilePath Ссылка на путь файла конфигурации
     * @param in_requestsFilePath Ссылка на путь файла запросов
     * @param in_answersFilePath Ссылка на путь файла ответов
     * @param in_precision Количество знаков после запятой
     * @param in_formatByWidth Ширина вывода
     */
    SearchEngine(const std::string& in_configFilePath, const std::string& in_requestsFilePath, const std::string& in_answersFilePath, int in_precision, int in_formatByWidth)
    : configSearchEngine(in_configFilePath, in_requestsFilePath),

      converterJSONObj(configSearchEngine.getConfigJSON(), configSearchEngine.getRequestsJSON(), in_precision),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests(), in_precision),
      answersFilePath{in_answersFilePath}, formatByWidth{in_formatByWidth}

    {
        //Логировать сообщение о программе
        kav::Logger::info(converterJSONObj.about());
    }

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

        /**
         * Инициализирует класс
         * @param in_configFilePath Ссылка на путь файла конфигурации
         * @param in_requestsFilePath Ссылка на путь файла запросов
         */
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

        //Путь файла конфигурации
        std::string configFilePath;
        //Путь файла запросов
        std::string requestsFilePath;
        //JSON-объект конфигурации
        JSON configJSON;
        //JSON-объект запросов
        JSON requestsJSON;

        /**
         * Инициализировать (настроить) класс
         */
        void initialize();

    };

    /**
     * Объект чтения и хранения параметров для настройки класса SearchEngine
     */
    ConfigSearchEngine configSearchEngine;

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
     * Путь файла ответов
     */
    std::string answersFilePath;

    /**
     * Ширина вывода
     */
    int formatByWidth;

    /**
     * Записать в JSON-файл результаты поиска
     * @param objectJSON Ссылка на JSON-объект для записи
     * @param filePath Ссылка на путь файла
     * @param formatByWidth Ширина вывода
     */
    void writeAnswersToFile(const JSON& objectJSON, const std::string& filePath, int formatByWidth);

    /**
     * Читать документы из файлов
     * @param filePaths Ссылка на контейнер путей файлов
     * @return Контейнер документов
     */
    std::vector<std::string> readDocsFromFiles(const std::vector<std::string>& filePaths);

};



#endif //SEARCH_ENGINE_SEARCHENGINE_H
