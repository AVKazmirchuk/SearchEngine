//
// Created by Alexander on 08.01.2026.
//



#include "gtest/gtest.h"

#include "requests.h"

#include "testGeneral.h"



//Запустить проверку на создание объекта, обновление базы запросов по const l-ref,
// и получение ссылки на базу запросов
TEST(TestUpdateRequests, byConstLRef)
{
    //Создать объект запросов
    Requests requests;

    //Обновить базу запросов
    requests.updateRequests(Bases::requests());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (requests.getRequests() == Bases::requests());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, обновление базы запросов по r-ref,
// и получение ссылки на базу запросов
TEST(TestUpdateRequests, byRRef)
{
    //Создать объект запросов
    Requests requests;

    //Установить временной переменной базу запросов
    std::vector<std::string> tmpRequests{Bases::requests()};

    //Обновить базу запросов
    requests.updateRequests(std::move(tmpRequests));

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (requests.getRequests() == Bases::requests());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, очистку базы запросов,
// и получение ссылки на базу запросов
TEST(TestClearRequests, clearRequests)
{
    //Создать объект запросов
    Requests requests;

    //Обновить базу запросов
    requests.updateRequests(Bases::requests());

    //Обнулить результат операции
    bool result{};

    //Очистить базу запросов
    requests.clearRequests();

    //Установить результат операции
    result = requests.getRequests().empty();

    //Проверить утверждение
    ASSERT_TRUE(result);
}