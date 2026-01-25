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
}//Проверка одного сообщения, с исключениями*/



//Проверить время сообщения
TEST(TestLogger, timeOfMessage)
{
    //Обнулить результат операции
    bool result{};

    //Получить текущий момент времени
    std::chrono::system_clock::time_point nowBefore{std::chrono::system_clock::now()};

    //Получить строку из момента времени
    std::string strTimePoint{timePointToString(nowBefore)};

    //Логировать событие
    kav::Logger::info(strTimePoint);

    //Получить текущий момент времени
    std::chrono::system_clock::time_point nowAfter{std::chrono::system_clock::now()};

    //Получить строку лог-файла
    std::string logLine{getLogLine(strTimePoint)};

    //Получить момент времени записи сообщения в лог-файл
    std::chrono::system_clock::time_point messageTime{getTimePointFromString(logLine)};

    //Момент времени записи сообщения должен быть в пределах до и после моментов времени
    if (messageTime > nowBefore && messageTime < nowAfter)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время использования файла
TEST(TestLogger, fileUsageTime_seconds)
{
    //Создать объект логирования событий
    //kav::Logger logger(ProgramArguments::configLoggerFilePath_usage_1sec(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole_no());
    //std::this_thread::sleep_for(std::chrono::seconds(1));

    //Обнулить результат операции
    bool result{};

    std::filesystem::path pathOfLogBeforeChecking{kav::Logger::getCurrentLogPath()};

    kav::Logger::info(pathOfLogBeforeChecking.string());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    kav::Logger::info(pathOfLogBeforeChecking.string());

    if (pathOfLogBeforeChecking != kav::Logger::getCurrentLogPath())
    {
        result =true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

