//
// Created by Alexander on 24.01.2026.
//



#include "gtest/gtest.h"

#include "kav/operationFileAndJSON.h"

#include "testGeneral.h"



//Вспомогательная функция для проверки времени использования файла
bool checkFileUsageTime(const std::string &configLoggerFilePath, std::chrono::seconds seconds)
{
    //Обнулить результат операции
    bool result{};

    //Удалить все файлы из директории лог-файлов
    std::filesystem::remove_all(ProgramArguments::logsFolderName());
    std::filesystem::create_directory("Logs");

    //Изменить конфигурацию логгера. Создать новый файл для записи. Время использования файла 1 секунда
    kav::Logger::reset(configLoggerFilePath);
    //Ожидать появление нового файла
    std::this_thread::sleep_for(seconds);

    //Получить путь текущего файла логирования
    std::string pathOfLogBeforeResetting{getLastFilePath()};

    //Изменить конфигурацию логгера. Создать новый файл для записи. Время использования файла 1 секунда
    kav::Logger::reset(configLoggerFilePath);
    //Ожидать появление нового файла
    std::this_thread::sleep_for(seconds);


    //Получить путь текущего файла логирования
    std::string pathOfLogAfterResetting{getLastFilePath()};

    //Подсчитать количество лог-файлов в директории
    int filesNumber{};
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        ++filesNumber;
    }

    //Получить время создания файлов, прочитав их первые записи
    std::chrono::system_clock::time_point timePointBeforeResetting{getTimePointFromFile(pathOfLogBeforeResetting)};
    std::chrono::system_clock::time_point timePointAfterResetting{getTimePointFromFile(pathOfLogAfterResetting)};

    std::cout << "pathOfLogBeforeResetting: " << pathOfLogBeforeResetting << ", " << "pathOfLogAfterChecking: " << pathOfLogAfterResetting;
    //Если пути файлов разные и количество лог-файлов равно 2 и время создания файлов отличаются
    if (pathOfLogBeforeResetting != pathOfLogAfterResetting && filesNumber == 2 &&
    (timePointAfterResetting > timePointBeforeResetting))
    {
        //Условие выполнено
        result = true;
    }

    return result;
}



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
TEST(TestLogger, usage_1sec)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_1sec(), ProgramArguments::seconds_1());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время использования файла
TEST(TestLogger, usage_3sec)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_3sec(), ProgramArguments::seconds_3());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

