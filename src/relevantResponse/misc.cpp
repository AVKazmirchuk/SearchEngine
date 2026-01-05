//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>

#include "relevantResponse.h"



void RelevantResponse::sortByDescendingRelevance()
{
    //Для каждого запроса
    for (auto& request : relevantResponses)
    {
        //Сортировать документы
        std::stable_sort(request.begin(), request.end(),
                         [] (const RelativeIndex& a, const RelativeIndex& b)
                         {
                             //По убыванию релевантности
                             return a.rank > b.rank;
                         });
    }
}

void RelevantResponse::addDocumentsWithZeroRank()
{
    //Количество документов
    std::size_t numberOfDocuments{discoverNumberOfDocuments()};

    //По каждому запросу
    for (std::size_t idRequest{}; idRequest < preparedRequests.size(); ++idRequest)
    {
        //Добавить (заполнить) в контейнер записи документов с нулевым рангом
        //Для каждого документа
        for (std::size_t docID{}; docID < numberOfDocuments; ++docID)
        {
            //Определить, есть ли ID текущего документа в контейнере
            auto pos{std::find_if(relevantResponses[idRequest].begin(), relevantResponses[idRequest].end(),
                                  [docID = docID](const auto &relativeIndex)
                                  {
                                      return relativeIndex.docID == docID;
                                  })};

            //Если ID текущего документа отсутствует
            if (pos == relevantResponses[idRequest].end())
            {
                //Записать в контейнер структуру относительного индекса
                relevantResponses[idRequest].push_back({docID, 0.0f});
            }
        }
    }
}

const std::vector<std::vector<RelativeIndex>>& RelevantResponse::getRelevantResponses()
{
    return relevantResponses;
}

void RelevantResponse::clearRelevantResponses()
{
    relevantResponses.clear();
}