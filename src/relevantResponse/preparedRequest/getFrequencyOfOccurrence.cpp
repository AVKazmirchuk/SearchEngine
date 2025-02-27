//
// Created by Alexander on 23.02.2025.
//



#include "relevantResponse.h"



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