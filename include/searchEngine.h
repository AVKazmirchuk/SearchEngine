//
// Created by Alexander on 18.02.2025.
//

#ifndef SEARCH_ENGINE_SEARCHENGINE_H
#define SEARCH_ENGINE_SEARCHENGINE_H

#include <iostream>

#include "converterJSON.h"
#include "documents.h"
#include "invertedIndex.h"
#include "requests.h"
#include "relevantResponse.h"
#include "readWriteTextFile.h"
#include "readWriteJSONFile.h"
#include "general.h"



class SearchEngine
{

public:

    /**
     * Инициализирует объекты классов
     */
    SearchEngine()

    : converterJSONObj(ReadWriteJSONFile().readJSONFile(constants::configFilePath),
                       ReadWriteJSONFile().readJSONFile(constants::requestsFilePath)),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())

    {}

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
     */
    std::vector<std::vector<std::pair<int, float>>> exportRelevantResponses();

private:

    ConverterJSON converterJSONObj;
    //Документы
    Documents documentsObj;
    //Инвертированный индекс
    InvertedIndex invertedIndexObj;
    //Запросы
    Requests requestsObj;
    //Релевантные ответы
    RelevantResponse relevantResponseObj;

};



#endif //SEARCH_ENGINE_SEARCHENGINE_H
