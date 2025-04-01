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

void RelevantResponse::countRelevanceOfResponses() {
    //Изменить внешний размер базы релевантности ответов по количеству запросов
    relevantResponses.resize(preparedRequests.size());

    //Количество документов
    std::size_t numberOfDocuments{discoverNumberOfDocuments()};

    //По каждому запросу
    for (std::size_t idRequest{}; idRequest < preparedRequests.size(); ++idRequest) {
        //Временная таблица связи ID документа и частоты вхождения слов запроса в документах
        std::vector<std::vector<float>> IDDocumentRequest(numberOfDocuments,
                                                          std::vector<float>(preparedRequests[idRequest].size()));

        //Для каждого слова запроса
        for (std::size_t idWord{}; idWord < preparedRequests[idRequest].size(); ++idWord) {
            //Для каждой  структуры инвертированного индекса
            for (const auto &entry: getInvertedIndexStructures(preparedRequests[idRequest][idWord])) {
                //Записать в ячейку значение частоты вхождения слова
                IDDocumentRequest[entry.docID][idWord] = static_cast<float>(entry.count);
            }
        }
        //Для каждого документа
        for (std::size_t docID{}; docID < IDDocumentRequest.size(); ++docID) {
            //Абсолютная релевантность
            float absoluteRelevance{};
            //Рассчитать абсолютную релевантность
            absoluteRelevance = std::accumulate(IDDocumentRequest[docID].begin(), IDDocumentRequest[docID].end(),
                                                absoluteRelevance);

            //Записать в ячейку структуру относительного индекса
            relevantResponses[idRequest].push_back({docID, absoluteRelevance});
            //Определить максимальную абсолютную релевантность
            maxAbsoluteRelevance = std::max(maxAbsoluteRelevance, absoluteRelevance);
        }
    }
}