//
// Created by Alexander on 19.02.2025.
//



#include "searchEngine.h"



std::vector<std::vector<std::pair<std::uint64_t, float>>> SearchEngine::exportRelevantResponses()
{
    //Временная база релевантности ответов другого типа структуры относительного индекса
    std::vector<std::vector<std::pair<std::uint64_t, float>>> answers(relevantResponseObj.getRelevantResponses().size());

    //Для каждого запроса
    for (std::size_t requestId{}; requestId < relevantResponseObj.getRelevantResponses().size(); ++requestId)
    {
        //Для каждого индекса относительности
        for(auto& relativeIndexID : relevantResponseObj.getRelevantResponses()[requestId])
        {
            //Добавить текущему списку запросов индексы относительности из соотвествующего списка запросов базы релевантности ответов
            answers[requestId].emplace_back(relativeIndexID.docID, relativeIndexID.rank);
        }
    }

    //Вернуть преобразованную базу релевантности ответов
    return answers;
}
