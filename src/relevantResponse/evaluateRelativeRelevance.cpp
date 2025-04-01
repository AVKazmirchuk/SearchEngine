//
// Created by Alexander on 18.02.2025.
//



#include <cmath>

#include "relevantResponse.h"
#include "general.h"



float RelevantResponse::roundUpToPrecision(float value)
{
    //Вычислить порядок числа в соответствии с точностью
    int numberOrder{static_cast<int>(std::pow(10, constants::precision))};
    //Округлить значение в соответствии с точностью
    return std::round(value*numberOrder)/numberOrder;
}

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