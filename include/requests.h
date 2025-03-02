//
// Created by Alexander on 15.02.2025.
//

#ifndef SEARCH_ENGINE_REQUESTS_H
#define SEARCH_ENGINE_REQUESTS_H



#include <string>
#include <vector>



/*
 * Класс реализует загрузку и хранение базы запросов
 */
class Requests
{

public:

    Requests() = default;

    /**
     * Обновить базу запросов
     * @param in_requests База запросов
     */
    void updateRequests(const std::vector<std::string>& in_requests);

    /**
     * Обновить базу запросов
     * @param in_requests База запросов
     */
    void updateRequests(std::vector<std::string>&& in_requests);

    /**
     * Получить ссылку на базу запросов
     * @return Ссылка на базу запросов
     */
    const std::vector<std::string>& getRequests();

    /**
     * Очистить базу запросов
     */
    void clearRequests();

private:

    /**
     * База запросов
     */
    std::vector<std::string> requests;

};



#endif //SEARCH_ENGINE_REQUESTS_H
