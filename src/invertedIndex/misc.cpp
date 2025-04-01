//
// Created by Alexander on 31.03.2025.
//



#include "invertedIndex.h"



const std::map<std::string, std::vector<Entry>>& InvertedIndex::getInvertedIndexes()
{
    //Вернуть ссылку на базу инвертированных индексов
    return invertedIndexes;
}

void InvertedIndex::sortByAscendingDocumentID()
{
    //Для каждого элемента базы инвертированного индекса
    for (auto& element : invertedIndexes)
    {
        //Сортировать список структур инвертированного индекса
        std::sort(element.second.begin(), element.second.end(),
                  [] (const Entry& a, const Entry& b)
                  {
                      //По возрастанию ID документа
                      return a.docID < b.docID;
                  });
    }
}

void InvertedIndex::clearInvertedIndexes()
{
    invertedIndexes.clear();
}