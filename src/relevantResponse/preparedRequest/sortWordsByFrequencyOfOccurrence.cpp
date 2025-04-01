//
// Created by Alexander on 31.01.2025.
//



#include <algorithm>

#include "relevantResponse.h"



std::vector<Entry> RelevantResponse::PreparedRequest::getInvertedIndexStructures(const std::string& word)
{
    //Слово в базе инвертированных индексов существует
    if (invertedIndexes.find(word) != invertedIndexes.end())
    {
        //Возвратить список структур инвертированного индекса
        return invertedIndexes.find(word)->second;
    }
    else
        //Слово в базе инвертированных индексов не существует
    {
        //Возвратить пустой список структур инвертированного индекса
        return std::vector<Entry>{};
    }
}

std::size_t RelevantResponse::PreparedRequest::getFrequencyOfOccurrence(const std::string& word)
{
    //Частота вхождения слова в документах
    std::size_t count{};

    //Для каждой структуры инвертированного индекса
    for (const auto entry: getInvertedIndexStructures(word))
    {
        //Суммировать частоту вхождения слова
        count += entry.count;
    }

    return count;
}

void RelevantResponse::PreparedRequest::sortWordsByFrequencyOfOccurrence()
{
    //Для каждого подготовленного запроса
    for (auto& preparedRequest : preparedRequests)
    {
        //Сортировать слова по частоте вхождения в документах
        std::sort(preparedRequest.begin(), preparedRequest.end(),
                  [this] (const auto& a, const auto& b)
                  {
                      return getFrequencyOfOccurrence(a) < getFrequencyOfOccurrence(b);
                  });
    }
}