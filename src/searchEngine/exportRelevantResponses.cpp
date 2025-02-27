//
// Created by Alexander on 19.02.2025.
//



#include "searchEngine.h"



std::vector<std::vector<std::pair<int, float>>> SearchEngine::exportRelevantResponses()
{
    //Временная база релевантности ответов другого типа структуры относительного индекса
    std::vector<std::vector<std::pair<int, float>>> answers;

    //Для каждого запроса
    for (std::size_t requestId{}; requestId < relevantResponseObj.getRelevantResponses().size(); ++requestId)
    {
        //Добавить пустой список
        answers.emplace_back(std::vector<std::pair<int, float>>{});

        //Каждую структуру относительного индекса
        for (auto& relativeIndex : relevantResponseObj.getRelevantResponses()[requestId])
        {
            //Добавить во временную базу релевантности ответов
            answers[requestId].emplace_back(relativeIndex.docID, relativeIndex.rank);
        }
    }

    return answers;
}