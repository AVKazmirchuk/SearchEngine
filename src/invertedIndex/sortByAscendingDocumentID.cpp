//
// Created by Alexander on 30.03.2025.
//



#include "invertedIndex.h"



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