//
// Created by Alexander on 24.01.2026.
//



#include "gtest/gtest.h"

#include "kav/operationFileAndJSON.h"

#include "testGeneral.h"


//Проверка одного сообщения, без исключений

//Проверить функцию на уровень логирования debug
TEST(TestLogger, debug)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::debug(timePointForEachFile);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForEachFile, ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestLogger, info)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::info(timePointForEachFile);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForEachFile, ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestLogger, wrning)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::warning(timePointForEachFile);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForEachFile, ProgramArguments::errorLevel_warning());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestLogger, error)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::error(timePointForEachFile);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForEachFile, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
TEST(TestLogger, fatal)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::fatal(timePointForEachFile);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForEachFile, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//Проверка одного сообщения, без исключений



//Проверка одного сообщения, с исключениями

//Проверить функцию на уровень логирования debug
TEST(TestLogger, debugWithException)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::debug(ProgramArguments::messageForException(), std::runtime_error(timePointForEachFile));

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevelForException(timePointForEachFile, ProgramArguments::messageForException(), ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestLogger, infoWithException)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::info(ProgramArguments::messageForException(), std::runtime_error(timePointForEachFile));

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevelForException(timePointForEachFile, ProgramArguments::messageForException(), ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestLogger, wrningWithException)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::warning(ProgramArguments::messageForException(), std::runtime_error(timePointForEachFile));

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevelForException(timePointForEachFile, ProgramArguments::messageForException(), ProgramArguments::errorLevel_warning());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestLogger, errorWithException)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::error(ProgramArguments::messageForException(), std::runtime_error(timePointForEachFile));

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevelForException(timePointForEachFile, ProgramArguments::messageForException(), ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
TEST(TestLogger, fatalWithException)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    kav::Logger::fatal(ProgramArguments::messageForException(), std::runtime_error(timePointForEachFile));

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevelForException(timePointForEachFile, ProgramArguments::messageForException(), ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}