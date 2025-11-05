//
// Created by Alexander on 19.02.2025.
//



#include "searchEngine.h"
#include "timer.h"

#include "DispatcherOperationValidity.h"



std::vector<std::string> SearchEngine::readDocsFromFiles(const std::vector<std::string>& filePaths)
{
    //Прочитать документы
    return DispatcherOperationValidity::readMultipleTextFiles(converterJSONObj.getFilePaths(), 14).first;
}

void SearchEngine::readDocsFromFilesRef(const std::vector<std::string>& filePaths, std::pair<std::vector<std::string>, ErrorCode> &documents)
{
    //Прочитать документы
    DispatcherOperationValidity::readMultipleTextFilesRef(converterJSONObj.getFilePaths(), documents, 10);
}

void SearchEngine::writeAnswersToFile(const JSON& objectJSON, const std::string& filePath, int formatByWidth)
{
    //Записать результаты поиска
    DispatcherOperationValidity::writeJSONFile(filePath, objectJSON, formatByWidth);
}

void SearchEngine::searchModifiedAll()
{
    //Очистить список документов
    documentsObj.clearDocuments();
Timer t2;
    //Обновить список документов из файлов
    documentsObj.updateDocuments(readDocsFromFiles(converterJSONObj.getFilePaths()));
    //std::pair<std::vector<std::string>, ErrorCode> documents;
    //readDocsFromFilesRef(converterJSONObj.getFilePaths(), documents);
    //documentsObj.updateDocuments(std::move(documents.first));
std::cout << '\n' << t2.elapsed() << '\n';
    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes(10);

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