//
// Created by Alexander on 26.02.2025.
//



#include "converterJSON.h"



float ConverterJSON::accumulateRank(const std::vector<std::vector<std::pair<std::uint64_t, float>>>& answers, std::size_t requestId)
{
    return std::accumulate(answers[static_cast<std::uint64_t>(requestId)].cbegin(), answers[static_cast<std::uint64_t>(requestId)].cend(), static_cast<float>(0.0),
                           [](float rank, const std::pair<std::uint64_t, float>& index)
                           {
                               return rank += index.second;
                           });
}