//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include "invertedIndex.h"

#include <iostream>

std::pair<std::size_t, const unsigned int> InvertedIndex::countNumberOfThreads()
{
    //Фактическое количество потоков
    unsigned int numberOfThreads{};
    //Количество документов в потоке
    std::size_t difference{};

    //Если желаемое (дополнительное) количество потоков определено
    if (desiredNumberOfThreads > 0)
    {
        //Определить фактическое количество потоков.
        //Можно вывести формулу определения в зависимости от количества файлов, объёма файлов и желаемого количества потоков.
        //Но нужны для этого элементарные статистические данные.
        numberOfThreads = desiredNumberOfThreads;

        //Определить количество документов в потоке
        difference = documents.size() / numberOfThreads;

        //Если все потоки не охватывают все файлы
        if (documents.size() % numberOfThreads)
        {
            //Увеличить количество потоков
            ++difference;
        }
    }

    //Вернуть количество документов в потоке и количество потоков
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