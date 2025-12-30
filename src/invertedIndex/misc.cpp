//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include "invertedIndex.h"

#include <iostream>

std::pair<std::size_t, const unsigned int> InvertedIndex::countNumberOfThreads()
{
    //Количество дополнительных потоков
    //Если количество документов меньше либо равно желаемого количества потоков - использовать количество потоков равным количеству документов.
    //В противном случае - использовать желаемое количество потоков.
    unsigned int numberOfThreads{};
    //Количество документов в потоке
    std::size_t difference{};

    if (desiredNumberOfThreads > 0)
    {
        numberOfThreads = (documents.size() <= desiredNumberOfThreads ? documents.size() : desiredNumberOfThreads);




        //Определить разницу количества документов между потоками
        difference = documents.size() / numberOfThreads;

        if (documents.size() % numberOfThreads)
        {
            //Увеличить количество потоков
            ++difference;
        }
    }

    std::cout << desiredNumberOfThreads << " " << numberOfThreads << '\n';
    std::getchar();

    return {difference, numberOfThreads};
}

const std::map<std::string, std::vector<Entry>>& InvertedIndex::getInvertedIndexes()
{
    //Вернуть ссылку на базу инвертированных индексов
    return invertedIndexes;
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