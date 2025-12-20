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
#include "kav/logger.h"



/**
 * Класс организует взаимодействие между другими классами
 */
class SearchEngine
{

public:

    /**
     * Инициализирует объекты всех классов
     * @param in_configFilePath Ссылка на путь файла конфигурации
     * @param in_requestsFilePath Ссылка на путь файла запросов
     * @param in_answersFilePath Ссылка на путь файла ответов
     * @param in_documentsBaseOrPathsBase Признак формирования базы документов или путей файлов документов
     * @param in_precision Количество знаков после запятой
     * @param in_formatByWidth Ширина вывода
     * @param in_desiredNumberOfThreads Желаемое количество потоков
     * @param in_maximumAllowableErrorsNumber Максимальное количество непрочитанных файлов (допустимых ошибок)
     */
    SearchEngine(const std::string& in_configFilePath, const std::string& in_requestsFilePath, const std::string& in_answersFilePath, const std::string& in_documentsBaseOrPathsBase, unsigned int in_precision, const unsigned int in_formatByWidth, const unsigned int in_desiredNumberOfThreads, const std::size_t in_maximumAllowableErrorsNumber)
    : converterJSONObj(in_configFilePath, in_requestsFilePath, in_precision),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments(), in_maximumAllowableErrorsNumber, in_desiredNumberOfThreads, in_documentsBaseOrPathsBase),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests(), in_precision),
      answersFilePath{in_answersFilePath}, documentsBaseOrPathsBase{in_documentsBaseOrPathsBase}, formatByWidth{in_formatByWidth}, desiredNumberOfThreads{in_desiredNumberOfThreads}, maximumAllowableErrorsNumber{in_maximumAllowableErrorsNumber}

    {
        //Логировать сообщение о программе
        kav::Logger::info(converterJSONObj.about());
    }

    /**
     * Инициализирует объекты всех классов
     * @param in_configFilePath Ссылка на путь файла конфигурации
     * @param in_requestsFilePath Ссылка на путь файла запросов
     * @param in_answersFilePath Ссылка на путь файла ответов
     * @param in_precision Количество знаков после запятой
     * @param in_formatByWidth Ширина вывода
     * @param in_desiredNumberOfThreads Желаемое количество потоков
     * @param in_maximumAllowableErrorsNumber Максимальное количество непрочитанных файлов (допустимых ошибок)
     */
    SearchEngine(std::string&& in_configFilePath, std::string&& in_requestsFilePath, std::string&& in_answersFilePath, std::string&& in_documentsBaseOrPathsBase, unsigned int in_precision, const unsigned int in_formatByWidth, const unsigned int in_desiredNumberOfThreads, const std::size_t in_maximumAllowableErrorsNumber)
            : converterJSONObj(std::move(in_configFilePath), std::move(in_requestsFilePath), in_precision),
              documentsObj{},
              invertedIndexObj(documentsObj.getDocuments(), in_maximumAllowableErrorsNumber, in_desiredNumberOfThreads, in_documentsBaseOrPathsBase),
              requestsObj{},
              relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests(), in_precision),
              answersFilePath{std::move(in_answersFilePath)}, documentsBaseOrPathsBase{in_documentsBaseOrPathsBase}, formatByWidth{in_formatByWidth}, desiredNumberOfThreads{in_desiredNumberOfThreads}, maximumAllowableErrorsNumber{in_maximumAllowableErrorsNumber}

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

private:

    /**
     * JSON-объекты
     */
    ConverterJSON converterJSONObj;

    /**
     * Документы или пути файлов документов
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
    const std::string answersFilePath;

    /**
     * Признак формирования базы документов или путей файлов документов
     */
    const std::string documentsBaseOrPathsBase;

    /**
     * Ширина вывода
     */
    const unsigned int formatByWidth;

    /**
     * Желаемое количество потоков
     */
    const unsigned int desiredNumberOfThreads;

    /**
     * Максимальное количество непрочитанных файлов
     */
    const std::size_t maximumAllowableErrorsNumber;

    /**
     * Определить: формировать базу документов или путей файлов документов
     */
    void determineDocumentsBaseOrPathsBase();

    /**
     * Преобразовать базу релевантности ответов в другой тип
     * @return Преобразованная база релевантности ответов
     */
    std::vector<std::vector<std::pair<std::uint64_t, float>>> exportRelevantResponses();

    /**
     * Записать в JSON-файл результаты поиска
     * @param filePath Ссылка на путь файла
     */
    void writeAnswersToFile(const std::string& filePath);

    /**
     * Читать документы из файлов. Используется косвенно для определения уровня логирования
     * @param filePaths Ссылка на контейнер путей файлов
     * @return Контейнер документов
     */
    std::vector<std::string> readDocsFromFiles(const std::vector<std::string>& filePaths) const;

    //Для тестирования передачи контейнера по ссылке
    //void readDocsFromFilesRef(const std::vector<std::string>& filePaths, ResultOfReadMultipleTextFiles &documents);

};



#endif //SEARCH_ENGINE_SEARCHENGINE_H
