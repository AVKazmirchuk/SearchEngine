//
// Created by Alexander on 18.02.2025.
//



#include <algorithm>

#include "entry.h"
#include "relevantResponse.h"



std::size_t RelevantResponse::discoverNumberOfDocuments()
{
    //ID документа
    std::size_t documentID{0};

    //По каждому элементу базы инвертированных индексов
    for (const auto& pairOfWordAndInvertedIndexStructures : invertedIndexes)
    {
        //Для каждой структуры инвертированного индекса
        std::for_each(pairOfWordAndInvertedIndexStructures.second.begin(), pairOfWordAndInvertedIndexStructures.second.end(),
                      [&documentID] (const Entry& elem)
                      {
                          //Определить максимальный ID документа
                          if (elem.docID > documentID) documentID = elem.docID;
                      }
        );
    }

    //Возвратить количество документов
    return ++documentID;
}