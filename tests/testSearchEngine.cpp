//
// Created by Alexander on 09.01.2026.
//



#include "gtest/gtest.h"

//#include "dispatcherOperations.h"
#include "searchEngine.h"

#include "testGeneral.h"



//Запустить проверку на создание объекта, рассчёт релевантности ответов, получение файла ответов
TEST(TestSearchModifiedAll, searchModifiedAll)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект
    SearchEngine searchEngine(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::answersFilePath(),
                              ProgramArguments::documentsBaseOrPathsBase(),
                              ProgramArguments::precision(),
                              ProgramArguments::formatByWidth(),
                              ProgramArguments::desiredNumberOfThreads(),
                              ProgramArguments::maximumAllowableErrorsNumber());

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (DispatcherOperations::readJSONFile(ProgramArguments::answersFilePath(), "", ErrorLevel::fatal).first == Bases::answersJSON());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, рассчёт релевантности ответов, получение файла ответов, количество знаков после запятой
TEST(TestSearchModifiedAll, precision_3)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект
    SearchEngine searchEngine(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::answersFilePath(),
                              ProgramArguments::documentsBaseOrPathsBase(),
                              ProgramArguments::precision_3(),
                              ProgramArguments::formatByWidth(),
                              ProgramArguments::desiredNumberOfThreads(),
                              ProgramArguments::maximumAllowableErrorsNumber());

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (DispatcherOperations::readJSONFile(ProgramArguments::answersFilePath(), "", ErrorLevel::fatal).first == Bases::answersJSON_3());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта (отсутствует файл конфигурации)
TEST(TestSearchModifiedAll, configFilePath_missing)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать объект
        SearchEngine searchEngine(ProgramArguments::configFilePath_missing(), ProgramArguments::requestsFilePath(),
                                  ProgramArguments::answersFilePath(),
                                  ProgramArguments::documentsBaseOrPathsBase(),
                                  ProgramArguments::precision(),
                                  ProgramArguments::formatByWidth(),
                                  ProgramArguments::desiredNumberOfThreads(),
                                  ProgramArguments::maximumAllowableErrorsNumber());
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта (отсутствует файл запросов)
TEST(TestSearchModifiedAll, requestsFilePath_missing)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать объект
        SearchEngine searchEngine(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath_missing(),
                                  ProgramArguments::answersFilePath(),
                                  ProgramArguments::documentsBaseOrPathsBase(),
                                  ProgramArguments::precision(),
                                  ProgramArguments::formatByWidth(),
                                  ProgramArguments::desiredNumberOfThreads(),
                                  ProgramArguments::maximumAllowableErrorsNumber());
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта (отсутствует файл ответов)
TEST(TestSearchModifiedAll, answersFilePath_empty)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    //Создать объект
    SearchEngine searchEngine(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(),
                                  ProgramArguments::answersFilePath_empty(),
                                  ProgramArguments::documentsBaseOrPathsBase(),
                                  ProgramArguments::precision(),
                                  ProgramArguments::formatByWidth(),
                                  ProgramArguments::desiredNumberOfThreads(),
                                  ProgramArguments::maximumAllowableErrorsNumber());

    try
    {
    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, признак формирования базы документов или путей файлов документов
TEST(TestSearchModifiedAll, documentsBaseOrPathsBase_no)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    //Создать объект
    SearchEngine searchEngine(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(),
                              ProgramArguments::answersFilePath(),
                              ProgramArguments::documentsBaseOrPathsBase_no(),
                              ProgramArguments::precision(),
                              ProgramArguments::formatByWidth(),
                              ProgramArguments::desiredNumberOfThreads(),
                              ProgramArguments::maximumAllowableErrorsNumber());

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //Установить результат операции
    result = (searchEngine.getDocumentsBaseOrPathsBase() == ProgramArguments::documentsBaseOrPathsBase_no() &&
            DispatcherOperations::readJSONFile(ProgramArguments::answersFilePath(), "", ErrorLevel::fatal).first == Bases::answersJSON());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, действительное максимальное количество непрочитанных файлов
TEST(TestSearchModifiedAll, maximumAllowableErrorsNumber_1)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    //Создать объект
    SearchEngine searchEngine(ProgramArguments::configFilePath_file003_missing(), ProgramArguments::requestsFilePath(),
                              ProgramArguments::answersFilePath(),
                              ProgramArguments::documentsBaseOrPathsBase(),
                              ProgramArguments::precision(),
                              ProgramArguments::formatByWidth(),
                              ProgramArguments::desiredNumberOfThreads(),
                              ProgramArguments::maximumAllowableErrorsNumber_1());

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //Установить результат операции
    result = (searchEngine.getMaximumAllowableErrorsNumber() == ProgramArguments::maximumAllowableErrorsNumber_1() &&
            DispatcherOperations::readJSONFile(ProgramArguments::answersFilePath(), "", ErrorLevel::fatal).first == Bases::answersJSON_file003_missing());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, действительное количество потоков (три потока)
TEST(TestSearchModifiedAll, desiredNumberOfThreads_3)
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    //std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Обнулить результат операции
    bool result{};

    //Создать объект
    SearchEngine searchEngine(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(),
                              ProgramArguments::answersFilePath(),
                              ProgramArguments::documentsBaseOrPathsBase(),
                              ProgramArguments::precision(),
                              ProgramArguments::formatByWidth(),
                              ProgramArguments::desiredNumberOfThreads_3(),
                              ProgramArguments::maximumAllowableErrorsNumber());

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //Установить результат операции
    result = (searchEngine.getNumberOfThreads() == ProgramArguments::desiredNumberOfThreads_3());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

