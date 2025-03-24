//
// Created by Alexander on 27.01.2025.
//



#include "converterJSON.h"
#include "general.h"
#include "relevantResponse.h"



/*
 Конструирует JSON-объект вида:

{
  "answers": {
    "request001": {
      "result": "true",
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 2,
          "rank": 0.94737
        }
      ]
    },
    "request002": {
      "result": "true",
        "docid": 1,
        "rank": 0.07018
    },
    "request003": {
      "result": "false"
    }
  }
}*/



void ConverterJSON::setAnswersJSON(const std::vector<std::vector<std::pair<std::uint64_t , float>>>& answers, int maxResponses)
{
    //Максимальное количество ответов не должно быть меньше 1
    maxResponses = maxResponses < 1 ? 1 : maxResponses;

    //Определить максимальное количество ответов в зависимости от действительно возможных
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
            /*
             * Ответов нет. Модифицировать JSON-объект вида:
             *
             * {
             *   "answers": {
             *   ...
             *     "request003": {
             *     "result": "false"
             *     }
             *   }
             * }
             *
             */
            answersJSON[constants::answersStr][currentRequest] = {{constants::resultStr, constants::falseStr}};
            //Перейти к следующему запросу
            continue;
        }

        /*
         * Ответы есть. Модифицировать JSON-объект вида:
         *
         * {
         *   "answers": {
         *   ...
         *     "request002": {
         *     "result": "true",
         *   ...
         *     }
         *   }
         * }
         *
         */
        answersJSON[constants::answersStr][currentRequest] = {{constants::resultStr, constants::trueStr}};

        //Рассчитать количество ответов с ненулевым рангом
        const std::size_t countOfNonZeroRank{static_cast<size_t>(std::count_if(answers[requestId].cbegin(), answers[requestId].cend(),
                                                                               [epsilon=epsilon](const std::pair<std::uint64_t, float>& index)
                                                                               {
                                                                                    //Вернуть признак ненулевого ранга
                                                                                    return index.second >= epsilon;
                                                                               }))};

        //Запрос имеет один ответ
        if (countOfNonZeroRank == 1)
        {
            /*
             * Модифицировать JSON-объект вида:
             *
             * {
             *   "answers": {
             *   ...
             *     "request002": {
             *     "result": "true",
             *     "docid": 1,
             *     "rank": 0.07018
             *     }
             *   ...
             *   }
             * }
             *
             */
            answersJSON[constants::answersStr][currentRequest].push_back({constants::docIdStr, answers[requestId][0].first});
            answersJSON[constants::answersStr][currentRequest].push_back({constants::rankStr, answers[requestId][0].second});
            //Перейти к следующему запросу
            continue;
        }

        //Запрос имеет более одного ответа
        //Для каждой структуры относительного индекса
        for (std::size_t relativeIndex{0}; relativeIndex < updatedMaxResponses; ++relativeIndex)
        {
            //Ранг меньше точности (ранг считается нулевым)
            if (answers[requestId][relativeIndex].second < epsilon)
                //Перейти к следующему запросу
                break;

            /*
             * Добавить ID документа и его ранг текущего запроса. Модифицировать JSON-объект вида:
             *
             * {
             *   "answers": {
             *     "request001": {
             *       "result": "true",
             *       "relevance": [
             *         {
             *           "docid": 0,
             *           "rank": 1.0
             *         },
             *         {
             *           "docid": 2,
             *           "rank": 0.94737
             *         }
             *       ]
             *   }
             *   ...
             * }
             *
             */
            answersJSON[constants::answersStr][currentRequest][constants::relevanceStr].push_back(
                    {{constants::docIdStr, answers[requestId][relativeIndex].first},
                     {constants::rankStr, answers[requestId][relativeIndex].second}});
        }
    }
}