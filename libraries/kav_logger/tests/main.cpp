//
// Created by Alexander on 24.01.2026.
//



#include "gtest/gtest.h"

#include "testGeneral.h"



int main()
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Создать объект получения сообщения в очереди
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configWriterMessageFilePath_loggerTest());

    //Запустить монитор в другом потоке
    std::future<void> fut = std::async(&kav::LoggerMonitor::run, &loggerMonitor);

    loggerMonitorExtern = &loggerMonitor;

    //Создать объект логирования событий
    kav::Logger logger(ProgramArguments::configLoggerFilePath_size_200_bytes(), ProgramArguments::configWriterMessageFilePath_loggerTest(), ProgramArguments::launchConsole_yes());

    //Ожидать
    waitFileWrite(ProgramArguments::waitFileWrite_micro_10());

    //Запустить все тесты
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}