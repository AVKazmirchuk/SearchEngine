//
// Created by Alexander on 27.01.2025.
//



#include <iostream>

#include "converterJSON.h"
#include "general.h"
#include "relevantResponse.h"



void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers, int maxResponses)
{
    //Максимальное количество ответов не должно быть меньше 1
    maxResponses = maxResponses < 1 ? 1 : maxResponses;

    //Определить максимальное количества ответов в зависимости от действительно возможных
    std::size_t updatedMaxResponses{(answers[0].size() <= maxResponses ? answers[0].size() : maxResponses)};

    //Точность (количество знаков после запятой) вывода относительной релевантности
    float epsilon{1/static_cast<float>(std::pow(10, constants::precision))};

    //Для каждого запроса
    for (std::size_t requestId{}; requestId < answers.size(); ++requestId)
    {
        //Преобразовать ID запроса в строку
        std::string currentRequest{convertIdtoStr(requestId, constants::requestStr)};

        //Суммарный ранг ответов меньше точности
        if (accumulateRank(answers, requestId) < epsilon)
        {
            //Ответов нет. Модифицировать JSON-объект
            answersJSON[constants::answersStr][currentRequest] = {{constants::resultStr, constants::falseStr}};
            //Пропустить текущую итерацию
            continue;
        }

        //Ответы есть. Модифицировать JSON-объект
        answersJSON[constants::answersStr][currentRequest] = {{constants::resultStr, constants::trueStr}};

        //Рассчитать количество ответов с ненулевым рангом
        const std::size_t countOfNonZeroRank{static_cast<size_t>(std::count_if(answers[requestId].cbegin(), answers[requestId].cend(),
                                                                               [epsilon=epsilon](const std::pair<std::size_t, float>& index)
                                                                               {
                                                                                   return index.second >= epsilon;
                                                                               }))};

        //Запрос имеет один ответ
        if (countOfNonZeroRank == 1)
        {
            //Модифицировать JSON-объект
            answersJSON[constants::answersStr][currentRequest].push_back({constants::docIdStr, answers[requestId][0].first});
            answersJSON[constants::answersStr][currentRequest].push_back({constants::rankStr, answers[requestId][0].second});
            //Пропустить текущую итерацию
            continue;
        }

        //Для каждой структуры относительного индекса
        for (std::size_t relativeIndex{0}; relativeIndex < updatedMaxResponses; ++relativeIndex)
        {
            //Ранг меньше точности
            if (answers[requestId][relativeIndex].second < epsilon)
                //Выйти из цикла
                break;

            //Добавить ID документа и его ранг текущего запроса. Модифицировать JSON-объект
            answersJSON[constants::answersStr][currentRequest][constants::relevanceStr].push_back(
                    {{constants::docIdStr, answers[requestId][relativeIndex].first},
                     {constants::rankStr, answers[requestId][relativeIndex].second}});
        }
    }
}