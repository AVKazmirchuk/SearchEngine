//
// Created by Alexander on 30.03.2025.
//



#include "gtest/gtest.h"

#include "kav/logger.h"

#include "testGeneral.h"



int main()
{
    //Создать объект логирования событий
    kav::Logger logger(ProgramArguments::configLoggerFilePath(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole_2());

    //Запустить все тесты
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}