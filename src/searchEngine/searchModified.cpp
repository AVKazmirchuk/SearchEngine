//
// Created by Alexander on 19.02.2025.
//


#include "general.h"
#include "searchEngine.h"

#include "dispatcherDetermineValidity.h"



std::vector<std::string> SearchEngine::readDocsFromFiles(const std::vector<std::string>& filePaths)
{
    //Прочитать документы
    return DispatcherDetermineValidity::readMultipleTextFiles(converterJSONObj.getFilePaths()).first;
}

void SearchEngine::writeAnswersToFile(const JSON& objectJSON, const std::string& filePath, int formatByWidth)
{
    //Записать результаты поиска
    DispatcherDetermineValidity::writeJSONFile(filePath, objectJSON, formatByWidth);
}

void SearchEngine::searchModifiedAll()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Обновить список документов из файлов
    documentsObj.updateDocuments(readDocsFromFiles(converterJSONObj.getFilePaths()));

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes();

    //Очистить список запросов
    requestsObj.clearRequests();

    //Обновить список запросов из файла
    requestsObj.updateRequests(converterJSONObj.getRequests());

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //Записать в JSON-объект результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses(), converterJSONObj.getMaxResponses());

    //Записать в JSON-файл результаты поиска
    writeAnswersToFile(converterJSONObj.getAnswersJSON(), answersFilePath, formatByWidth);
}

void SearchEngine::searchModifiedDocuments()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Обновить список документов из файлов
    documentsObj.updateDocuments(readDocsFromFiles(converterJSONObj.getFilePaths()));

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes();

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //Записать в файл answers.json результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses(), converterJSONObj.getMaxResponses());

    //Записать в JSON-файл результаты поиска
    writeAnswersToFile(converterJSONObj.getAnswersJSON(), answersFilePath, formatByWidth);
}

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
    writeAnswersToFile(converterJSONObj.getAnswersJSON(), answersFilePath, formatByWidth);
}