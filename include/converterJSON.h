//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <list>
#include <thread>
#include <mutex>
#include <future>

#include "nlohmann/json.hpp"

#include "general.h"



/**
 * Класс реализует работу с JSON-объектами
 */
class ConverterJSON
{

public:

    ConverterJSON(const JSON& in_configJSON, const JSON& in_requestsJSON)

    : configJSON(in_configJSON),
      requestsJSON(in_requestsJSON)

    {}

    ConverterJSON(JSON&& in_configJSON, JSON&& in_requestsJSON)

            : configJSON(std::move(in_configJSON)),
              requestsJSON(std::move(in_requestsJSON))

    {}

    /**
     * Получить список файлов документов
     * @return Список файлов документов
     */
    std::vector<std::string> getFilePaths();

    /**
     * Получить запросы
     * @return Запросы
     */
    std::vector<std::string> getRequests();

    /**
     * Получить значение максимального количества ответов
     * @return Значение максимального количества ответов
     */
    int getMaxResponses();

    /**
     * Записать в JSON-объект результаты поиска
     * @param answers Релевантность ответов
     * @param maxResponses Значение максимального количества ответов
     */
    void setAnswersJSON(const std::vector<std::vector<std::pair<int, float>>>& answers, int maxResponses);

    /**
     * Получить JSON-объект ответов
     * @return Ссылка на JSON-объект ответов
     */
    JSON& getAnswersJSON();

private:

    /**
     * JSON-объект конфигурации
     */
    JSON configJSON;

    /**
     * JSON-объект запросов
     */
    JSON requestsJSON;

    /**
     * JSON-объект ответов
     */
    JSON answersJSON;

    /**
     * Определить суммарный ранг
     * @param answers Ответы
     * @param requestId ID запроса
     * @return Суммарный ранг
     */
    float accumulateRank(const std::vector<std::vector<std::pair<int, float>>>& answers, std::size_t requestId);

    /**
     * Преобразовать Id запроса в строку
     * @param requestId ID запроса
     * @param str Начальная строка
     * @return Преобразованная строка
     */
    std::string convertIdtoStr(const std::size_t requestId, std::string str);

};

#endif //SEARCH_ENGINE_CONVERTERJSON_H
