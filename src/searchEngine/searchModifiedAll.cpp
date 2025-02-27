//
// Created by Alexander on 19.02.2025.
//


#include "general.h"
#include "searchEngine.h"





void SearchEngine::searchModifiedAll()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Обновить список документов из файлов
    documentsObj.updateDocuments(ReadWriteTextFile().readTextFile(converterJSONObj.getFilePaths()));

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes();

    //Очистить список запросов
    requestsObj.clearRequests();

    //Обновить список запросов из файла
    requestsObj.updateRequests(converterJSONObj.getRequests());

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //Записывает в файл answers.json результаты поиска, с учётом максимального количества ответов
    converterJSONObj.putAnswers(exportRelevantResponses(), converterJSONObj.getMaxResponses());

    ReadWriteJSONFile().writeJSONFile(converterJSONObj.getAnswersJSON(), constants::answersFilePath);
}