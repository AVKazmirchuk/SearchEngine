//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H



#include <future>
#include <list>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "constants.h"
#include "entry.h"



/**
 * Класс реализует инвертированную индексацию документов
 */
class InvertedIndex
{

public:

    /**
     * Инициализирует ссылку на базу документов или путей файлов документов
     * @param in_documents Ссылка на базу документов или путей файлов документов
     * @param in_maximumAllowableErrorsNumber Максимальное количество непрочитанных файлов
     * @param in_desiredNumberOfThreads Желаемое количество потоков
     * @param in_documentsBaseOrPathsBase Признак формирования базы документов или путей файлов документов
     */
    InvertedIndex(const std::vector<std::string>& in_documents,
                           const std::size_t in_maximumAllowableErrorsNumber = 0,
                           const unsigned int in_desiredNumberOfThreads = std::thread::hardware_concurrency(),
                           const std::string& in_documentsBaseOrPathsBase = Constants::default_documentsBaseOrPathsBase())
    : documents{in_documents},
      maximumAllowableErrorsNumber{in_maximumAllowableErrorsNumber},
      desiredNumberOfThreads{in_desiredNumberOfThreads},
      documentsBaseOrPathsBase{in_documentsBaseOrPathsBase}
    {}

    /**
     * Обновить базу инвертированных индексов
     */
    void updateInvertedIndexes();

    /**
     * Получить ссылку на базу инвертированных индексов
     * @return Ссылка на базу инвертированных индексов
     */
    const std::map<std::string, std::vector<Entry>>& getInvertedIndexes();

private:

    //ОСНОВНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Ссылка на базу документов или путей файлов документов
     */
    const std::vector<std::string>& documents;

    /**
     * База инвертированных индексов
     */
    std::map<std::string, std::vector<Entry>> invertedIndexes;

    /**
     * Очистить базу инвертированных индексов
     */
    void clearInvertedIndexes();



    //ВСПОМОГАТЕЛЬНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Мьютекс на поиск и добавление слова в базе инвертированных индексов
     */
    //std::mutex mutexFindAddWord;

    /**
     * Мьютекс на поиск и добавление структуры инвертированного индекса в базе инвертированных индексов
     */
    //std::mutex mutexFindAddEntry;

    /**
     * Признак формирования базы документов или путей файлов документов
     */
    const std::string documentsBaseOrPathsBase;

    /**
     * Желаемое количество потоков
     */
    const unsigned int desiredNumberOfThreads;

    /**
     * Максимальное количество непрочитанных файлов
     */
    const std::size_t maximumAllowableErrorsNumber;

    /**
     * Сразу определить слово (выделить) в документе
     */
    void(InvertedIndex::*defineWordOrReadDocumentAtBeginning)(std::size_t, const std::string&, std::map<std::string, std::vector<Entry>>&){&InvertedIndex::defineWord};

    //Начальное количество баз инвертированного индекса для каждого потока. Наименьшее время - при значении 2.
    unsigned int initialBasesNumberInStream{2};

    /**
     * Определить количество потоков
     * @return Пара количества документов обрабатываемое одним потокам и количества дополнительных потоков
     */
    std::pair<std::size_t, const unsigned int> countNumberOfThreads();

    /**
     * Запустить инвертированную индексацию документов в отдельных потоках
     */
    void startInvertedIndexing();

    /**
     * Определить слово (выделить) в документе
     * @param docID ID документа
     * @param document Ссылка на документ или путь файла документа
     * @param invertedIndexesForThread Ссылка на инвретированные индексы каждого потока
     */
    void defineWord(std::size_t docID, const std::string& document, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread);

    /**
     * Прочитать документ по его пути
     * @param docID ID документа
     * @param documentPath Ссылка на документ или путь файла документа
     * @param invertedIndexesForThread Ссылка на инвретированные индексы каждого потока
     */
    void readDocument(std::size_t docID, const std::string& documentPath, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread);

    /**
     * Слить базы инвертированного индекса подготовленные в разных потоках
     * @param futures Контейнер результатов потоков
     */
    void mergeInvertedIndexBases(std::vector<std::future<std::map<std::basic_string<char>, std::vector<Entry>>>> &futures);

    /**
     * Добавить слово и структуру инвертированного индекса в базу инвертированных индексов
     * @param word Ссылка на слово
     * @param docID ID документа
     * @param invertedIndexesForThread Ссылка на инвретированные индексы каждого потока
     */
    void addWord(const std::string& word, std::size_t docID, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread);

    /**
     * Сортировать базу инвертированного индекса по возрастанию ID документа
     */
    //void sortByAscendingDocumentID();

};



#endif //SEARCH_ENGINE_INVERTEDINDEX_H
