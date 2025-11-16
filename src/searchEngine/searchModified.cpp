//
// Created by Alexander on 19.02.2025.
//



#include "searchEngine.h"
#include "timer.h"

#include "DispatcherOperations.h"



std::vector<std::string> SearchEngine::readDocsFromFiles(const std::vector<std::string>& filePaths)
{
    //Прочитать документы
    return DispatcherOperations::readMultipleTextFiles(converterJSONObj.getFilePaths(), desiredNumberOfThreads, maximumAllowableErrorsNumber).documentsAndErrors.first;
}

//Для тестирования передачи контейнера по ссылке
/*void SearchEngine::readDocsFromFilesRef(const std::vector<std::string>& filePaths, ResultOfReadMultipleTextFiles &documents)
{
    //Прочитать документы
    DispatcherOperations::readMultipleTextFilesRef(converterJSONObj.getFilePaths(), documents);
}*/

void SearchEngine::writeAnswersToFile(const std::string& filePath)
{
    //Записать результаты поиска
    DispatcherOperations::writeJSONFile(filePath, converterJSONObj.getAnswersJSON(), formatByWidth);
}

void SearchEngine::searchModifiedAll()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Для замеров
    //Timer t;

    //Обновить список документов из файлов
    documentsObj.updateDocuments(readDocsFromFiles(converterJSONObj.getFilePaths()));

    //Для тестирования передачи контейнера по ссылке
    /*ResultOfReadMultipleTextFiles documents;
    readDocsFromFilesRef(converterJSONObj.getFilePaths(), documents);
    documentsObj.updateDocuments(std::move(documents.documentsAndErrors.first));*/

    //Для замеров
    //std::cout << '\n' << t.elapsed() << '\n';

    //Для замеров
    Timer t;

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes(desiredNumberOfThreads);

    //Для замеров
    std::cout << '\n' << t.elapsed() << '\n';
    std::getchar();

    //Очистить список запросов
    requestsObj.clearRequests();

    //Обновить список запросов из файла
    requestsObj.updateRequests(converterJSONObj.getRequests());

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //Записать в JSON-объект результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses(), converterJSONObj.getMaxResponses());

    //Записать в JSON-файл результаты поиска
    writeAnswersToFile(answersFilePath);
}

void SearchEngine::searchModifiedDocuments()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Обновить список документов из файлов
    documentsObj.updateDocuments(readDocsFromFiles(converterJSONObj.getFilePaths()));

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes(desiredNumberOfThreads);

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //Записать в файл answers.json результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses(), converterJSONObj.getMaxResponses());

    //Записать в JSON-файл результаты поиска
    writeAnswersToFile(answersFilePath);
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
    writeAnswersToFile(answersFilePath);
}