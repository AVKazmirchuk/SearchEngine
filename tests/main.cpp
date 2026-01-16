//
// Created by Alexander on 30.03.2025.
//



#include "gtest/gtest.h"

#include "kav/logger.h"

#include "testGeneral.h"



int main()
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    std::filesystem::create_directory("Logs");

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект логирования событий
    kav::Logger logger(ProgramArguments::configLoggerFilePath(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole_2());

    //Запустить все тесты
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}