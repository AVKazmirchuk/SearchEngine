//
// Created by Alexander on 18.02.2025.
//



#include <cmath>

#include "relevantResponse.h"



void RelevantResponse::evaluateRelativeRelevance()
{
    //Для каждого запроса
    for (auto& request : relevantResponses)
    {
        //Для структуры относительного индекса
        for (auto& relativeIndex : request)
        {
            //Записать относительную релевантность
            relativeIndex.rank = roundUpToPrecision(relativeIndex.rank / maxAbsoluteRelevance);
        }
    }
}