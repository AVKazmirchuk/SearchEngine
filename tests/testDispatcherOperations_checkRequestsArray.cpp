//
// Created by Alexander on 16.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции checkRequestsArray
//Проверить функцию на уровень логирования
bool testCheckRequestsArray(ErrorLevel errorLevel, const std::string& strErrorLevel)
{
    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
    DispatcherOperations::checkRequestsArray(Bases::requestsEmptyJSON(), timePoint, errorLevel);

    //Возвратить соответствие фактического уровня логирования ожидаемому
    return isMatchingErrorLevel(timePoint, strErrorLevel);
}

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_checkRequestsArray, debug)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckRequestsArray(ErrorLevel::debug, ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestDispatcherOperations_checkRequestsArray, info)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckRequestsArray(ErrorLevel::info, ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestDispatcherOperations_checkRequestsArray, wrning)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckRequestsArray(ErrorLevel::warning, ProgramArguments::errorLevel_warn());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestDispatcherOperations_checkRequestsArray, error)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckRequestsArray(ErrorLevel::error, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
TEST(TestDispatcherOperations_checkRequestsArray, fatal)
{

    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Обнулить результат операции
    bool result{};

    try
    {
        //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
        DispatcherOperations::checkRequestsArray(Bases::requestsEmptyJSON(), timePoint, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException &exception)
    {
        result = true;
    }

    //Возвратить соответствие фактического уровеня логирования ожидаемому
    result = result && isMatchingErrorLevel(timePoint, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);

}//Тестирование функции checkRequestsArray