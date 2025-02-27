//
// Created by Alexander on 23.02.2025.
//



#include "relevantResponse.h"



void RelevantResponse::PreparedRequest::updatePreparedRequests()
{
    //Очистить подготовленную базу запросов
    clearPreparedRequests();

    //Разбить базу запросов на отдельные слова и заполнить ими подготовленную базу запросов
    separateRequestsByWords();

    //Преобразовать подготовленные запросы, в запросы, содержащие уникальные слова
    convertPreparedRequestsToUniqueWords();

    //Сортировать слова по частоте вхождения в документы
    sortWordsByFrequencyOfOccurrence();
}