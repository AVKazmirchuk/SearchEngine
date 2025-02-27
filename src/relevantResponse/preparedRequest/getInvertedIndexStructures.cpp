//
// Created by Alexander on 27.01.2025.
//



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