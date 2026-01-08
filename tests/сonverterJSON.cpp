//
// Created by Alexander on 08.01.2026.
//



#include "gtest/gtest.h"

#include "converterJSON.h"

#include "testGeneral.h"



//Запустить проверку на создание объекта по const l-ref, получение списка путей файлов документов
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

//Запустить проверку на создание объекта по const l-ref, получение запросов
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

//Запустить проверку на создание объекта по const l-ref, получение количества знаков после запятой
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

//Запустить проверку на создание объекта по r-ref, получение списка путей файлов документов
TEST(TestConverterJSON, getFilePathsByRRef)
{
    //Установить соответствия имени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Установить временной переменной путь файла конфигурации
    std::string tmpConfigFilePath{ProgramArguments::configFilePath()};
    //Установить временной переменной путь файла запросов
    std::string tmpRequestsFilePath{ProgramArguments::requestsFilePath()};

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(std::move(tmpConfigFilePath), std::move(tmpRequestsFilePath), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (converterJson.getFilePaths() == Bases::filePaths());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта по r-ref, получение запросов
TEST(TestConverterJSON, getRequestsByRRef)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Установить временной переменной путь файла конфигурации
    std::string tmpConfigFilePath{ProgramArguments::configFilePath()};
    //Установить временной переменной путь файла запросов
    std::string tmpRequestsFilePath{ProgramArguments::requestsFilePath()};

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(std::move(tmpConfigFilePath), std::move(tmpRequestsFilePath), ProgramArguments::precision());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (converterJson.getRequests() == Bases::requests());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта по r-ref, получение количества знаков после запятой
TEST(TestConverterJSON, getPrecisionByRRef)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Установить временной переменной путь файла конфигурации
    std::string tmpConfigFilePath{ProgramArguments::configFilePath()};
    //Установить временной переменной путь файла запросов
    std::string tmpRequestsFilePath{ProgramArguments::requestsFilePath()};

    //Создать объект JSON-конвертера
    ConverterJSON converterJson(std::move(tmpConfigFilePath), std::move(tmpRequestsFilePath), ProgramArguments::precision());

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

//Запустить проверку на создание объекта, получение информации о программе
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

