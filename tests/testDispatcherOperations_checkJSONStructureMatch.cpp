//
// Created by Alexander on 16.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции checkJSONStructureMatch
//Проверить функцию на уровень логирования
bool testCheckJSONStructureMatch(ErrorLevel errorLevel, const std::string& strErrorLevel)
{
    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Проверить структуру JSON-файла на соответствие шаблону, указав отметку времени (будет использоваться для поиска строки в лог-файле)
    DispatcherOperations::checkJSONStructureMatch(ProgramArguments::configFilePath(), Bases::configNotMatchJSON(), Bases::configJSON(), timePoint, errorLevel);

    //Возвратить соответствие фактического уровня логирования ожидаемому
    return isMatchingErrorLevel(timePoint, strErrorLevel);
}

//Проверить структуру JSON-файла на соответствие шаблону. Структура соответствует
TEST(TestDispatcherOperations_checkJSONStructureMatch, match)
{
    //Обнулить результат операции
    bool result{};

    //Проверить структуру JSON-файла на соответствие шаблону
    result = DispatcherOperations::checkJSONStructureMatch(ProgramArguments::configFilePath(), Bases::configJSON(), Bases::configJSON(), "", ErrorLevel::error) == ErrorCode::no_error;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить структуру JSON-файла на соответствие шаблону. Структура не соответствует
TEST(TestDispatcherOperations_checkJSONStructureMatch, notMatch)
{
    //Обнулить результат операции
    bool result{};

    //Проверить структуру JSON-файла на соответствие шаблону
    result = DispatcherOperations::checkJSONStructureMatch(ProgramArguments::configFilePath(), Bases::configNotMatchJSON(), Bases::configJSON(), "", ErrorLevel::error) == ErrorCode::error_json_structure_not_match;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_checkJSONStructureMatch, debug)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckJSONStructureMatch(ErrorLevel::debug, ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestDispatcherOperations_checkJSONStructureMatch, info)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckJSONStructureMatch(ErrorLevel::info, ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestDispatcherOperations_checkJSONStructureMatch, wrning)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckJSONStructureMatch(ErrorLevel::warning, ProgramArguments::errorLevel_warning());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestDispatcherOperations_checkJSONStructureMatch, error)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckJSONStructureMatch(ErrorLevel::error, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
TEST(TestDispatcherOperations_checkJSONStructureMatch, fatal)
{

    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Обнулить результат операции
    bool result{};

    try
    {
        //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
        DispatcherOperations::checkJSONStructureMatch(ProgramArguments::configFilePath(), Bases::configNotMatchJSON(), Bases::configJSON(), timePoint, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException &exception)
    {
        result = true;
    }

    //Возвратить соответствие фактического уровеня логирования ожидаемому
    result = result && isMatchingErrorLevel(timePoint, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);

}//Тестирование функции checkJSONStructureMatch