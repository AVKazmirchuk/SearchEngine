//
// Created by Alexander on 19.02.2025.
//


#include "general.h"
#include "searchEngine.h"



void SearchEngine::searchModifiedRequests()
{
    //Очистить список запросов
    requestsObj.clearRequests();

    //Обновить список запросов из файла
    requestsObj.updateRequests(converterJSONObj.getRequests());

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //Записать в файл answers.json результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses(), converterJSONObj.getMaxResponses());

    //Записать в JSON-файл результаты поиска
    ReadWriteJSONFile::writeJSONFile(converterJSONObj.getAnswersJSON(), constants::answersFilePath);
}