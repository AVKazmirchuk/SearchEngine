//
// Created by Alexander on 19.02.2025.
//



#include "searchEngine.h"
#include "timer.h"

#include "DispatcherOperations.h"



std::vector<std::string> SearchEngine::readDocsFromFiles(const std::vector<std::string>& filePaths) const
{
    //Прочитать документы
    return DispatcherOperations::readMultipleTextFiles(filePaths, desiredNumberOfThreads, maximumAllowableErrorsNumber).documentsAndErrors.first;
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

void SearchEngine::determineDocumentsBaseOrPathsBase()
{
    if (documentsBaseOrPathsBase == Constants::default_documentsBaseOrPathsBase())
    {
        //Обновить список документов из файлов
        documentsObj.updateDocuments(readDocsFromFiles(converterJSONObj.getFilePaths()));
        //Документы загружены в базу
        kav::Logger::info("Documents uploaded to the database");
    }
    else
    {
        //Обновить список путей файлов документов
        documentsObj.updateDocuments(converterJSONObj.getFilePaths());
        //Пути файлов документов загружены в базу
        kav::Logger::info("Document file paths uploaded to the database");
    }
}

void SearchEngine::searchModifiedAll()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Для замеров
    Timer t;

    //Определить: формировать базу документов или путей файлов документов
    determineDocumentsBaseOrPathsBase();

    //Для замеров
    std::cout << '\n' << t.elapsed() << '\n';
    std::getchar();

    //Для тестирования передачи контейнера по ссылке
    /*ResultOfReadMultipleTextFiles documents;
    readDocsFromFilesRef(converterJSONObj.getFilePaths(), documents);
    documentsObj.updateDocuments(std::move(documents.documentsAndErrors.first));*/

    //Для замеров
    //std::cout << '\n' << t.elapsed() << '\n';
    //std::getchar();

    //Для замеров
    //Timer t;

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes();

    //База инвертированного индекса обновлена
    kav::Logger::info("The base of the inverted index has been updated");

    //Для замеров
    //std::cout << '\n' << t.elapsed() << '\n';
    //std::getchar();

    //Очистить список запросов
    requestsObj.clearRequests();

    //Обновить список запросов из файла
    requestsObj.updateRequests(converterJSONObj.getRequests());

    //База запросов обновлена
    kav::Logger::info("The query database has been updated");

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //База релевантности ответов обновлена
    kav::Logger::info("The database of relevance of responses has been updated");

    //Записать в JSON-объект результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses());

    //JSON-объект файла ответа сформирован
    kav::Logger::info("The JSON object of the response file is formed");

    //Записать в JSON-файл результаты поиска
    writeAnswersToFile(answersFilePath);

    //Файл ответа выгружен
    kav::Logger::info("The response file has been uploaded");
}

void SearchEngine::searchModifiedDocuments()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Определить: формировать базу документов или путей файлов документов
    determineDocumentsBaseOrPathsBase();

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes();

    //База инвертированного индекса обновлена
    kav::Logger::info("The base of the inverted index has been updated");

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //База релевантности ответов обновлена
    kav::Logger::info("The database of relevance of responses has been updated");

    //Записать в JSON-объект результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses());

    //JSON-объект файла ответа сформирован
    kav::Logger::info("The JSON object of the response file is formed");

    //Записать в JSON-файл результаты поиска
    writeAnswersToFile(answersFilePath);

    //Файл ответа выгружен
    kav::Logger::info("The response file has been uploaded");
}

void SearchEngine::searchModifiedRequests()
{
    //Очистить список запросов
    requestsObj.clearRequests();

    //Обновить список запросов из файла
    requestsObj.updateRequests(converterJSONObj.getRequests());

    //База запросов обновлена
    kav::Logger::info("The query database has been updated");

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //База релевантности ответов обновлена
    kav::Logger::info("The database of relevance of responses has been updated");

    //Записать в JSON-объект результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses());

    //JSON-объект файла ответа сформирован
    kav::Logger::info("The JSON object of the response file is formed");

    //Записать в JSON-файл результаты поиска
    writeAnswersToFile(answersFilePath);

    //Файл ответа выгружен
    kav::Logger::info("The response file has been uploaded");
}