//
// Created by Alexander on 27.01.2025.
//



#include "relevantResponse.h"



void RelevantResponse::updateRelevantResponses()
{
    //Очистить базу релевантности ответов
    clearRelevantResponses();

    //Обновить подготовленную базу запросов
    preparedRequestObj.updatePreparedRequests();

    //Подсчитать частоту вхождения слова в документах по запросам и максимальную релевантность
    countRelevanceOfResponses();

    //Определить относительную релевантность
    evaluateRelativeRelevance();

    //Сортировать документы по убыванию релевантности
    sortByDescendingRelevance();
}

