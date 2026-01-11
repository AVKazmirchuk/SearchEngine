//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include "invertedIndex.h"

#include <iostream>

std::size_t InvertedIndex::countNumberOfThreads()
{
    //Количество документов в потоке
    std::size_t difference{};

    //Если желаемое (дополнительное) количество потоков определено
    if (desiredNumberOfThreads > 0)
    {
        //Определить количество документов в потоке
        difference = documents.size() / desiredNumberOfThreads;
        //Если все потоки не охватывают все файлы - увеличить количество документов в потоке
        if (documents.size() % desiredNumberOfThreads) ++difference;
        //Определить количество потоков
        numberOfThreads = documents.size() / difference;
        //Если все потоки не охватывают все файлы - увеличить количество потоков
        if (documents.size() % difference) ++numberOfThreads;
    }

    //Вернуть количество документов в потоке и количество потоков
    return difference;
}

const std::map<std::string, std::vector<Entry>>& InvertedIndex::getInvertedIndexes()
{
    //Вернуть ссылку на базу инвертированных индексов
    return invertedIndexes;
}

unsigned int InvertedIndex::getNumberOfThreads()
{
    return validNumberOfThreads;
}

const std::string& InvertedIndex::getDocumentsBaseOrPathsBase()
{
    if (validDocumentsBaseOrPathsBase) return Constants::default_documentsBaseOrPathsBase();

    return Constants::documentsBaseOrPathsBase_no();
}

std::size_t InvertedIndex::getMaximumAllowableErrorsNumber()
{
    return validMaximumAllowableErrorsNumber;
}

/*void InvertedIndex::sortByAscendingDocumentID()
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
}*/

void InvertedIndex::clearInvertedIndexes()
{
    invertedIndexes.clear();
}