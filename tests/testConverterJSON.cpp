//
// Created by Alexander on 08.01.2026.
//



#include "gtest/gtest.h"

#include "converterJSON.h"

#include "testGeneral.h"



//Запустить проверку на создание объекта, получение списка путей файлов документов
TEST(TestConverterJSON, getFilePaths)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (converterJson.getFilePaths() == Bases::filePaths());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, получение запросов
TEST(TestConverterJSON, getRequests)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (converterJson.getRequests() == Bases::requests());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, получение количества знаков после запятой
TEST(TestConverterJSON, getPrecision)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (converterJson.getPrecision() == ProgramArguments::precision());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, получение информации о программе
TEST(TestConverterJSON, about)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (converterJson.about() == Bases::about());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, получение максимального количества ответов
TEST(TestConverterJSON, maxResponses)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (converterJson.getMaxResponses() == ProgramArguments::maxResponses());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, запись в JSON-объект результатов поиска, получение ссылки на JSON-объект ответов,
TEST(TestConverterJSON, answersJSON)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Записать в JSON-объект результаты поиска
    converterJson.setAnswersJSON(Bases::exportRelativeIndex());

    //Установить результат операции
    result = (converterJson.getAnswersJSON() == Bases::answersJSON());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, запись в JSON-объект результатов поиска, получение ссылки на JSON-объект ответов,
//максимальное количество ответов
TEST(TestConverterJSON, answersJSON_2)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(ProgramArguments::configFilePath_2(), ProgramArguments::requestsFilePath(), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Записать в JSON-объект результаты поиска
    converterJson.setAnswersJSON(Bases::exportRelativeIndex());

    //Установить результат операции
    result = (converterJson.getAnswersJSON() == Bases::answersJSON_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта (отсутствует файл конфигурации)
TEST(TestConverterJSON, configFilePath_missing)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать объект JSON-конвертера
        ConverterJSON converterJson(ProgramArguments::configFilePath_missing(), ProgramArguments::requestsFilePath(),
                                    ProgramArguments::precision());
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта (отсутствует файл запросов)
TEST(TestConverterJSON, requestsFilePath_missing)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать объект JSON-конвертера
        ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath_missing(),
                                    ProgramArguments::precision());
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта (список путей файлов документов пуст)
TEST(TestConverterJSON, configFilePath_filesEmpty)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать объект JSON-конвертера
        ConverterJSON converterJson(ProgramArguments::configFilePath_filesEmpty(), ProgramArguments::requestsFilePath(),
                                    ProgramArguments::precision());
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта (список запросов пуст)
TEST(TestConverterJSON, requestsFilePath_requestsEmpty)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать объект JSON-конвертера
        ConverterJSON converterJson(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath_requestsEmpty(),
                                    ProgramArguments::precision());
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}