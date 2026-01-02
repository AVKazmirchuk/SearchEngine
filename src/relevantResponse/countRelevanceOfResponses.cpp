//
// Created by Alexander on 18.02.2025.
//



#include "algorithm"
#include <numeric>

#include "relevantResponse.h"



std::vector<Entry> RelevantResponse::getInvertedIndexStructures(const std::string& word)
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

void RelevantResponse::countRelevanceOfResponses()
{
    //Изменить внешний размер базы релевантности ответов по количеству запросов
    relevantResponses.resize(preparedRequests.size());

    //По каждому запросу
    for (std::size_t idRequest{}; idRequest < preparedRequests.size(); ++idRequest)
    {
        //Временная таблица связи ID документа и суммарной частоты вхождения слов запроса в документах
        std::map<std::size_t, float> IDDocumentRequest;

        //Для каждого слова запроса
        for (std::size_t idWord{}; idWord < preparedRequests[idRequest].size(); ++idWord)
        {
            //Для каждой  структуры инвертированного индекса
            for (const auto &entry: getInvertedIndexStructures(preparedRequests[idRequest][idWord]))
            {
                //Записать в контейнер значение суммарной частоты вхождения слова
                IDDocumentRequest[entry.docID] += static_cast<float>(entry.count);
            }
        }

        //Количество документов
        std::size_t numberOfDocuments{discoverNumberOfDocuments()};

        //Для каждого документа
        for (std::size_t docID{}; docID < numberOfDocuments; ++docID)
        {
            //Найти во временной таблице ID документа
            auto pos{IDDocumentRequest.find(docID)};
            //Если ID документа присутствует
            if (pos != IDDocumentRequest.end())
            {
                //Записать в контейнер структуру относительного индекса
                relevantResponses[idRequest].push_back({pos->first, pos->second});

                //Определить максимальную абсолютную релевантность
                maxAbsoluteRelevance = std::max(maxAbsoluteRelevance, pos->second);
            }
            else
            //ID документа отсутствует
            {
                //Записать в контейнер структуру относительного индекса
                relevantResponses[idRequest].push_back({docID, 0});
            }
        }
    }
}