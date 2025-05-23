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

const std::vector<std::vector<RelativeIndex>>& RelevantResponse::getRelevantResponses()
{
    return relevantResponses;
}

void RelevantResponse::clearRelevantResponses()
{
    relevantResponses.clear();
}