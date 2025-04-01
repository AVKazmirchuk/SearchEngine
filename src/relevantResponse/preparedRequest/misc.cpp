//
// Created by Alexander on 31.03.2025.
//



#include <set>

#include "relevantResponse.h"



const std::vector<std::vector<std::string>>& RelevantResponse::PreparedRequest::getPreparedRequests()
{
    return preparedRequests;
}

void RelevantResponse::PreparedRequest::clearPreparedRequests()
{
    preparedRequests.clear();
}

void RelevantResponse::PreparedRequest::convertPreparedRequestsToUniqueWords()
{
    //Для каждого подготовленного запроса
    for (auto& preparedRequest : preparedRequests)
    {
        //Преобразовать подготовленный запрос в запрос, содержащий уникальные слова
        std::set<std::string> uniqueWords(preparedRequest.begin(), preparedRequest.end());
        //Присвоить текущему подготовленному запросу преобразованный
        preparedRequest.assign(uniqueWords.begin(), uniqueWords.end());
    }
}