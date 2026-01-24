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
    std::filesystem::create_directory("Logs");

    //Создать объект логирования событий
    kav::Logger logger(ProgramArguments::configLoggerFilePath(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole_no());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    //Запустить все тесты
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}