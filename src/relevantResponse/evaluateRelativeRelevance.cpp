//
// Created by Alexander on 18.02.2025.
//



#include <cmath>

#include "relevantResponse.h"




float RelevantResponse::roundUpToPrecision(float value) const
{
    //Вычислить порядок числа в соответствии с точностью
    const unsigned int numberOrder{static_cast<unsigned int>(std::pow(10, precision))};
    //Округлить значение в соответствии с точностью
    return std::round(value*static_cast<float>(numberOrder))/static_cast<float>(numberOrder);
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