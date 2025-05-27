//
// Created by Alexander on 19.02.2025.
//


#include "general.h"
#include "searchEngine.h"

std::vector<std::string> SearchEngine::readDocsFromFiles(const std::vector<std::string>& filePaths)
{
    return ReadTextFile::readTextFile(converterJSONObj.getFilePaths());
}

void SearchEngine::writeAnswersToFile(const JSON& objectJSON, const std::string& filePath)
{
    ReadWriteJSONFile::writeJSONFile(objectJSON, filePath);
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
    writeAnswersToFile(converterJSONObj.getAnswersJSON(), constants::answersFilePath);
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
    writeAnswersToFile(converterJSONObj.getAnswersJSON(), constants::answersFilePath);
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
    writeAnswersToFile(converterJSONObj.getAnswersJSON(), constants::answersFilePath);
}