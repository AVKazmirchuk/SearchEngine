//
// Created by Alexander on 18.02.2025.
//

#ifndef SEARCH_ENGINE_SEARCHENGINE_H
#define SEARCH_ENGINE_SEARCHENGINE_H

#include <iostream>

#include <cstdint>



#include "converterJSON.h"
#include "documents.h"
#include "invertedIndex.h"
#include "requests.h"
#include "relevantResponse.h"
#include "readTextFile.h"
#include "readWriteJSONFile.h"
#include "general.h"



/**
 * Класс организует взаимодействие между другими классами
 */
class SearchEngine
{

public:

    /**
     * Инициализирует объекты классов
     * @param in_configJSON
     * @param in_requestsJSON
     */
    SearchEngine(const JSON& in_configJSON, const JSON& in_requestsJSON)

    : converterJSONObj(in_configJSON, in_requestsJSON),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())

    {
        Logger().info(converterJSONObj.about());
    }

    /**
     * Инициализирует объекты классов
     * @param in_configJSON
     * @param in_requestsJSON
     */
    SearchEngine(JSON&& in_configJSON, JSON&& in_requestsJSON)

    : converterJSONObj(std::move(in_configJSON), std::move(in_requestsJSON)),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())

    {
        Logger().info(converterJSONObj.about());
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

};



#endif //SEARCH_ENGINE_SEARCHENGINE_H
