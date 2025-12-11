//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include "invertedIndex.h"



std::pair<int, int> InvertedIndex::countNumberOfThreads(const unsigned int desiredNumberOfThreads)
{

    //Если база документов не пуста - определить размер базы по ней, в противном случае - по базе путей файлов документов
    std::size_t baseSize{!documents.empty() ? documents.size() : documentsPaths.size()};

    //Количество дополнительных потоков
    //Если количество документов меньше либо равно желаемого количества потоков - использовать количество потоков равным количеству документов.
    //В противном случае - использовать желаемое количество потоков.
    int numberOfThreads = baseSize <= desiredNumberOfThreads ? baseSize : desiredNumberOfThreads;

    //Определить количество документов обрабатываемое одним потокам
    std::size_t difference{baseSize / numberOfThreads};

    //Если количество документов делится с остатком
    if (baseSize % numberOfThreads)
    {
        //Увеличить количество потоков
        ++numberOfThreads;
    }

    return {difference, numberOfThreads};
}

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