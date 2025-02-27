//
// Created by Alexander on 26.02.2025.
//



#include "converterJSON.h"



float ConverterJSON::accumulateRank(const std::vector<std::vector<std::pair<int, float>>>& answers, std::size_t requestId)
{
    return std::accumulate(answers[requestId].cbegin(), answers[requestId].cend(), static_cast<float>(0.0),
                           [](float rank, const std::pair<std::size_t, float>& index)
                           {
                               return rank += index.second;
                           });
}