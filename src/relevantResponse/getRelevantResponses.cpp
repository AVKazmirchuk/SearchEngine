//
// Created by Alexander on 15.02.2025.
//



#include <vector>

#include "relevantResponse.h"
#include "relativeIndex.h"


//Получение списка релевантных ответов
const std::vector<std::vector<RelativeIndex>>& RelevantResponse::getRelevantResponses()
{
    return relevantResponses;
}