//
// Created by Alexander on 18.02.2025.
//



#include "relevantResponse.h"



void RelevantResponse::PreparedRequest::separateRequestsByWords()
{
    //Разделители слов
    const std::string  delims(" ");
    //Начальный и конечный (за последним символом) индексы слова
    std::string::size_type begIdx, endIdx;

    //Для каждого запроса из базы запросов
    for (auto& request : requests)
    {
        //Список слов текущего запроса
        std::vector<std::string> requestWords;

        //Искать начало первого слова
        begIdx = request.find_first_not_of(delims);

        //Искать начало первого слова
        while (begIdx != std::string::npos)
        {
            //Искать конец текущего слова
            endIdx = request.find_first_of(delims, begIdx);

            //Конец слова равен концу строки
            if (endIdx == std::string::npos)
            {
                //Конец слова - это конец строки
                endIdx = request.length();
            }

            //Добавить определённое слово в список
            requestWords.emplace_back(request, begIdx, endIdx - begIdx);

            //Искать начало следующего слова
            begIdx = request.find_first_not_of(delims, endIdx);
        }

        //Добавить список слов текущего запроса в подготовленную базу запросов
        preparedRequests.push_back(requestWords);
    }
}