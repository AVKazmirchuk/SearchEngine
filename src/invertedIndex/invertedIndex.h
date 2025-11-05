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

#include "entry.h"



/**
 * Класс реализует инвертированную индексацию документов
 */
class InvertedIndex
{

public:

    /**
     * Инициализирует ссылку на базу документов
     * @param in_documents Ссылка на базу документов
     */
    explicit InvertedIndex(const std::vector<std::string>& in_documents) : documents{in_documents} {}

    /**
     * Обновить базу инвертированных индексов
     */
    void updateInvertedIndexes(const int desiredNumberOfThreads = std::thread::hardware_concurrency());

    /**
     * Получить ссылку на базу инвертированных индексов
     * @return Ссылка на базу инвертированных индексов
     */
    const std::map<std::string, std::vector<Entry>>& getInvertedIndexes();

private:

    //ОСНОВНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Ссылка на базу документов
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
    std::mutex mutexFindAddWord;

    /**
     * Мьютекс на поиск и добавление структуры инвертированного индекса в базе инвертированных индексов
     */
    std::mutex mutexFindAddEntry;

    /**
     * Запустить инвертированную индексацию документов в отдельных потоках
     */
    void startInvertedIndexing(const int desiredNumberOfThreads);

    /**
     * Определить слово (выделить) в документе
     * @param docID ID документа
     * @param document Ссылка на документ
     */
    void defineWord(std::size_t docID, const std::string& document, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread);

    /**
     * Слить базы инвертированного индекса подготовленные в разных потоках
     * @param futures Контейнер результатов потоков
     * @param initialBasesNumberInStream Начальное количество баз инвертированного индекса для каждого потока
     */
    void mergeInvertedIndexBases(std::vector<std::future<std::map<std::basic_string<char>, std::vector<Entry>>>> &futures, int initialBasesNumberInStream);

    /**
     * Добавить слово и структуру инвертированного индекса в базу инвертированных индексов
     * @param word Ссылка на слово
     * @param docID ID документа
     */
    void addWord(const std::string& word, std::size_t docID, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread);

    /**
     * Сортировать базу инвертированного индекса по возрастанию ID документа
     */
    void sortByAscendingDocumentID();

};



#endif //SEARCH_ENGINE_INVERTEDINDEX_H
