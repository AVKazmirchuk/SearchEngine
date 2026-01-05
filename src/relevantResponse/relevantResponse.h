//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_RELEVANTRESPONSE_H
#define SEARCH_ENGINE_RELEVANTRESPONSE_H



#include <map>
#include <string>
#include <vector>

#include "entry.h"
#include "relativeIndex.h"



/**
 * Класс определяет релевантность ответов
 */
class RelevantResponse
{

public:

    /**
     * Инициализирует: ссылку на базу инвертированных индексов, cсылку на базу запросов,
     * , объект класса PreparedRequests, ссылку на подготовленную базу запросов
     * @param in_invertedIndexes Ссылка на базу инвертированных индексов
     * @param in_requests Ссылка на базу запросов
     * @param in_precision Количество знаков после запятой
     */
    RelevantResponse(const std::map<std::string, std::vector<Entry>>& in_invertedIndexes,
                     const std::vector<std::string>& in_requests, const unsigned int in_precision)

    : invertedIndexes{in_invertedIndexes},
      requests{in_requests},
      preparedRequestObj{in_invertedIndexes, in_requests},
      preparedRequests{preparedRequestObj.getPreparedRequests()},
      precision{in_precision}

    {}

    /**
     * Рассчитать релевантность ответов
     */
    void updateRelevantResponses();

    /**
     * Получить ссылку на базу релевантности ответов
     * @return Ссылка на базу релевантности ответов
     */
    const std::vector<std::vector<RelativeIndex>>& getRelevantResponses();

private:

    /**
     * Класс подготавливает базу запросов и хранит её
     */
    class PreparedRequest
    {

    public:

        /**
         * Инициализирует: ссылку на базу инвертированных индексов, ссылку на базу запросов
         * @param in_invertedIndexes Ссылка на базу инвертированных индексов
         * @param in_requests Ссылка на базу запросов
         */
        PreparedRequest(const std::map<std::string, std::vector<Entry>>& in_invertedIndexes,
                        const std::vector<std::string>& in_requests)

       : invertedIndexes{in_invertedIndexes},
         requests{in_requests}

        {}

        /**
         * Обновить подготовленную базу запросов
         */
        void updatePreparedRequests();

        /**
         * Получить ссылку на подготовленную базу запросов
         * @return Ссылка на подготовленную базу запросов
         */
        const std::vector<std::vector<std::string>>& getPreparedRequests();

    private:

        //ОСНОВНЫЕ ДАННЫЕ И ФУНКЦИИ

        /**
         * Ссылка на базу инвертированных индексов
         */
        const std::map<std::string, std::vector<Entry>>& invertedIndexes;

        /**
         * Ссылка на базу запросов
         */
        const std::vector<std::string>& requests;

        /**
         * Подготовленная база запросов
         */
        std::vector<std::vector<std::string>> preparedRequests;

        /**
         * Очистить подготовленную базу запросов
         */
        void clearPreparedRequests();



        //ВСПОМОГАТЕЛЬНЫЕ ДАННЫЕ И ФУНКЦИИ

        /**
         * Разбить базу запросов на отдельные слова и заполнить ими подготовленную базу запросов
         */
        void separateRequestsByWords();

        /**
         * Преобразовать подготовленные запросы, в запросы, содержащие уникальные слова
         */
        void convertPreparedRequestsToUniqueWords();

        /**
         * Сортировать слова по частоте вхождения в документах
         */
        void sortWordsByFrequencyOfOccurrence();

        /**
         * Получить частоту вхождения слова в документах
         * @param word слово
         * @return частота вхождения слова в документах
         */
        std::size_t getFrequencyOfOccurrence(const std::string& word);

        /**
         * Получить список структур инвертированного индекса соответствующего слова
         * @param word слово
         * @return Список структур инвертированного индекса соответствующего слова
         */
        std::vector<Entry> getInvertedIndexStructures(const std::string& word);

    };



    //ОСНОВНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Ссылка на базу инвертированных индексов
     */
    const std::map<std::string, std::vector<Entry>>& invertedIndexes;

    /**
     * Ссылка на базу запросов
     */
    const std::vector<std::string>& requests;

    /**
     * Объект вложенного класса PreparedRequest
     */
    PreparedRequest preparedRequestObj;

    /**
     * Ссылка на подготовленную базу запросов
     */
    const std::vector<std::vector<std::string>>& preparedRequests;

    /**
     * База релевантности ответов
     */
    std::vector<std::vector<RelativeIndex>> relevantResponses;

    /**
     * Очистить базу релевантности ответов
     */
    void clearRelevantResponses();



    //ВСПОМОГАТЕЛЬНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Максимальная абсолютная релевантность
     */
    float maxAbsoluteRelevance{};

    /**
     * Количество знаков после запятой
     */
    const unsigned int precision;

    /**
     * Определить количество документов
     * @return Количество документов
     */
    std::size_t discoverNumberOfDocuments();

    /**
     * Подсчитать частоту вхождения слова в документах по запросам и максимальную релевантность
     */
    void countRelevanceOfResponses();

    /**
     * Получить список структур инвертированного индекса соответствующего слова
     * @param word слово
     * @return Список структур инвертированного индекса соответствующего слова
     */
    std::vector<Entry> getInvertedIndexStructures(const std::string& word);

    /**
     * Определить относительную релевантность
     */
    void evaluateRelativeRelevance();

    /**
     * Округлить значение в соответствии с точностью
     * @param value Значение
     * @return Округлённое значение
     */
    [[nodiscard]] float roundUpToPrecision(float value) const;

    /**
     * Сортировать документы по убыванию релевантности
     */
    void sortByDescendingRelevance();

    /**
     * Добавить документы в базу с нулевым рангом
     */
    void addDocumentsWithZeroRank();

};



#endif //SEARCH_ENGINE_RELEVANTRESPONSE_H
