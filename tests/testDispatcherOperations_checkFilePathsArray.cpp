//
// Created by Alexander on 16.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции checkFilePathsArray
//Проверить функцию на уровень логирования
bool testCheckFilePathsArray(ErrorLevel errorLevel, const std::string& strErrorLevel)
{
    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Проверить JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
    DispatcherOperations::checkFilePathsArray(Bases::configEmptyJSON(), timePoint, errorLevel);

    //Возвратить соответствие фактического уровня логирования ожидаемому
    return isMatchingErrorLevel(timePoint, strErrorLevel);
}

//Массив путей файлов полон
TEST(TestDispatcherOperations_checkFilePathsArray, full)
{
    //Обнулить результат операции
    bool result{};

    //Проверить массив путей фалов
    result = DispatcherOperations::checkFilePathsArray(Bases::configFullJSON(), "", ErrorLevel::error) == ErrorCode::no_error;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Массив путей файлов пуст
TEST(TestDispatcherOperations_checkFilePathsArray, empty)
{
    //Обнулить результат операции
    bool result{};

    //Проверить массив путей фалов
    result = DispatcherOperations::checkFilePathsArray(Bases::configEmptyJSON(), "", ErrorLevel::error) == ErrorCode::error_file_paths_array_empty;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_checkFilePathsArray, debug)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckFilePathsArray(ErrorLevel::debug, ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestDispatcherOperations_checkFilePathsArray, info)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckFilePathsArray(ErrorLevel::info, ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestDispatcherOperations_checkFilePathsArray, warning)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckFilePathsArray(ErrorLevel::warning, ProgramArguments::errorLevel_warning());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestDispatcherOperations_checkFilePathsArray, error)
{
    //Обнулить результат операции
    bool result{};

    result = testCheckFilePathsArray(ErrorLevel::error, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
TEST(TestDispatcherOperations_checkFilePathsArray, fatal)
{

    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Обнулить результат операции
    bool result{};

    try
    {
        //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
        DispatcherOperations::checkFilePathsArray(Bases::configEmptyJSON(), timePoint, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException &exception)
    {
        result = true;
    }

    //Возвратить соответствие фактического уровеня логирования ожидаемому
    result = result && isMatchingErrorLevel(timePoint, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);

}//Тестирование функции checkFilePathsArray