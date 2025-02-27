//
// Created by Alexander on 31.01.2025.
//



#include <algorithm>

#include "relevantResponse.h"



void RelevantResponse::PreparedRequest::sortWordsByFrequencyOfOccurrence()
{
    //Для каждого подготовленного запроса
    for (auto& preparedRequest : preparedRequests)
    {
        //Сортировать слова по частоте вхождения в документах
        std::sort(preparedRequest.begin(), preparedRequest.end(),
                  [this] (const auto& a, const auto& b)
                  {
                      return getFrequencyOfOccurrence(a) < getFrequencyOfOccurrence(b);
                  });
    }
}