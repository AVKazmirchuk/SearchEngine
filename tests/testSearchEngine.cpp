//
// Created by Alexander on 09.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"
#include "searchEngine.h"

#include "testGeneral.h"



//Запустить проверку на создание объекта по const l-ref, получение файла ответов
TEST(TestSearchModifiedAll, byConstLRef)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект логирования событий
    kav::Logger logger(ProgramArguments::configLoggerFilePath(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole());

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
    result = (DispatcherOperations::readJSONFile(ProgramArguments::answersFilePath()).first == Bases::answersJSON());

    //Проверить утверждение
    ASSERT_TRUE(result);
}