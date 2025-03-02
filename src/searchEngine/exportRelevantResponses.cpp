//
// Created by Alexander on 19.02.2025.
//



#include "searchEngine.h"



std::vector<std::vector<std::pair<int, float>>> SearchEngine::exportRelevantResponses()
{
    //Временная база релевантности ответов другого типа структуры относительного индекса
    std::vector<std::vector<std::pair<int, float>>> answers(relevantResponseObj.getRelevantResponses().size());

    //Для каждого запроса
    for (std::size_t requestId{}; requestId < relevantResponseObj.getRelevantResponses().size(); ++requestId)
    {
        //Присвоить текущему списку запросов относительные индексы  из соотвествующего списка запросов базы релевантности ответов
        answers[requestId].assign(relevantResponseObj.getRelevantResponses()[requestId].cbegin(),
                                  relevantResponseObj.getRelevantResponses()[requestId].cend());
    }

    return answers;
}