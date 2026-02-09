//
// Created by Alexander on 24.01.2026.
//



#include "gtest/gtest.h"

#include "kav/operationFileAndJSON.h"

#include "testGeneral.h"



//Вспомогательная функция для проверки времени использования файла
bool checkFileUsageTime(const std::string &configLoggerFilePath, std::chrono::duration<double, std::ratio<1>> seconds)
{
    //Обнулить результат операции
    bool result{};

    //Удалить все файлы из директории лог-файлов
    std::filesystem::remove_all(ProgramArguments::logsFolderName());
    std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Изменить конфигурацию логгера. Создать новый файл для записи.
    kav::Logger::reset(configLoggerFilePath);
    //Ожидать
    //waitFileWrite(ProgramArguments::waitFileWrite_micro_10());

    //Получить путь текущего файла логирования
    std::string pathOfLogBeforeResetting{getLastFilePath()};

    //Ожидать время использования файла
    std::this_thread::sleep_for(seconds);

    //Изменить конфигурацию логгера. Создать новый файл для записи.
    kav::Logger::reset(configLoggerFilePath);
    //Ожидать появление нового файла
    //std::this_thread::sleep_for(seconds);
    //waitFileWrite(ProgramArguments::waitFileWrite_micro_10());


    //Получить путь текущего файла логирования
    std::string pathOfLogAfterResetting{getLastFilePath()};

    //Подсчитать количество лог-файлов в директории
    int filesNumber{};
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        ++filesNumber;
    }

    //Получить время создания файлов, прочитав их первые записи
    std::chrono::system_clock::time_point timePointBeforeResetting{getFirstTimePointFromFile(pathOfLogBeforeResetting)};
    std::chrono::system_clock::time_point timePointAfterResetting{getFirstTimePointFromFile(pathOfLogAfterResetting)};

    std::cout << "pathOfLogBeforeResetting: " << pathOfLogBeforeResetting << ", " << "pathOfLogAfterChecking: " << pathOfLogAfterResetting;
    //Если пути файлов разные и количество лог-файлов равно 2 и время создания файлов отличаются
    if (pathOfLogBeforeResetting != pathOfLogAfterResetting && filesNumber == 2 &&
            (timePointAfterResetting - timePointBeforeResetting) > seconds)
    {
        //Условие выполнено
        result = true;
    }

    return result;
}

//Вспомогательная функция для проверки времени хранения файла
bool checkFileStorageTime(const std::string &configLoggerFilePath, std::chrono::duration<double, std::ratio<1>> seconds)
{
    //Обнулить результат операции
    bool result{};

    //Удалить все файлы из директории лог-файлов
    std::filesystem::remove_all(ProgramArguments::logsFolderName());
    std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Изменить конфигурацию логгера. Создать новый файл для записи. Стандартная конфигурация
    kav::Logger::reset(ProgramArguments::configLoggerFilePath());
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //waitFileWrite(ProgramArguments::waitFileWrite_micro_10());

    //Получить путь текущего файла логирования
    std::string pathOfLogBeforeResetting{getLastFilePath()};

    //Получить время создания файла, прочитав его первую запись
    std::chrono::system_clock::time_point timePointBeforeResetting{getLastTimePointFromFile(pathOfLogBeforeResetting)};

    //Ожидать время хранения файла
    std::this_thread::sleep_for(seconds);

    //Изменить конфигурацию логгера. Создать новый файл для записи. Время хранения файла определено в конфигурации
    kav::Logger::reset(configLoggerFilePath);
    //Ожидать появление нового файла
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //waitFileWrite(ProgramArguments::waitFileWrite_micro_10());

    //Получить путь текущего файла логирования
    std::string pathOfLogAfterResetting{getLastFilePath()};

    //Получить время создания файла, прочитав его первую запись
    std::chrono::system_clock::time_point timePointAfterResetting{getLastTimePointFromFile(pathOfLogAfterResetting)};

    //Подсчитать количество лог-файлов в директории
    int filesNumber{};
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        ++filesNumber;
    }

    std::cout << "pathOfLogBeforeResetting: " << pathOfLogBeforeResetting << ", " << "pathOfLogAfterChecking: " << pathOfLogAfterResetting;
    //Если пути файлов разные и количество лог-файлов равно 2 и время создания файлов отличаются
    if (filesNumber == 1 && (timePointAfterResetting - timePointBeforeResetting) > seconds)
    {
        //Условие выполнено
        result = true;
    }

    return result;
}






//Проверка одного сообщения, без исключений

//Проверить функцию на уровень логирования debug
/*TEST(TestLogger, debug)
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
TEST(TestLogger, warning)
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
/*TEST(TestLogger, timeOfMessage)
{
    //Обнулить результат операции
    bool result{};

    //Получить текущий момент времени
    std::chrono::system_clock::time_point nowBefore{std::chrono::system_clock::now()};

    //Получить строку из момента времени
    std::string strTimePoint{timePointToString(nowBefore)};

    //Логировать событие
    kav::Logger::info(strTimePoint);

    //Ожидать
    waitFileWrite(ProgramArguments::waitFileWrite_micro_10());

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
}//*/

//Проверить время использования файла. Будет писаться в один файл
/*TEST(TestLogger, usageOneFile_3sec)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_3sec(), ProgramArguments::seconds_1());

    //Проверить утверждение
    ASSERT_FALSE(result);
}

//Проверить время использования файла. 1 скунда
TEST(TestLogger, usage_1sec)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_1sec(), ProgramArguments::seconds_1());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время использования файла. 3 секунды
TEST(TestLogger, usage_3sec)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_3sec(), ProgramArguments::seconds_3());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время использования файла. 6 секунд в минутах
TEST(TestLogger, usage_6sec_in_minutes)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_6sec_in_minutes(), ProgramArguments::seconds_6_in_minutes());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время использования файла. 6 секунд в часах
TEST(TestLogger, usage_6sec_in_hours)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_6sec_in_hours(), ProgramArguments::seconds_6_in_hours());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время использования файла. 6 секунд в днях
TEST(TestLogger, usage_6sec_in_days)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_6sec_in_days(), ProgramArguments::seconds_6_in_days());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время использования файла. 6 секунд в неделях
TEST(TestLogger, usage_6sec_in_weeks)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileUsageTime(ProgramArguments::configLoggerFilePath_usage_6sec_in_weeks(), ProgramArguments::seconds_6_in_weeks());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/

//Проверить время хранения файла. Будет два файла
/*TEST(TestLogger, storageTwoFile_3sec)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileStorageTime(ProgramArguments::configLoggerFilePath_storageTwoFile_3sec(), ProgramArguments::seconds_1());

    //Проверить утверждение
    ASSERT_FALSE(result);
}

//Проверить время хранения файла. 3 секунды
TEST(TestLogger, storage_3sec)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileStorageTime(ProgramArguments::configLoggerFilePath_storage_3sec(), ProgramArguments::seconds_3());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время хранения файла. 6 секунд в минутах
TEST(TestLogger, storage_6sec_in_minutes)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileStorageTime(ProgramArguments::configLoggerFilePath_storage_6sec_in_minutes(), ProgramArguments::seconds_6_in_minutes());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время хранения файла. 6 секунд в часах
TEST(TestLogger, storage_6sec_in_hours)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileStorageTime(ProgramArguments::configLoggerFilePath_storage_6sec_in_hours(), ProgramArguments::seconds_6_in_hours());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время хранения файла. 6 секунд в днях
TEST(TestLogger, storage_6sec_in_days)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileStorageTime(ProgramArguments::configLoggerFilePath_storage_6sec_in_days(), ProgramArguments::seconds_6_in_days());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить время хранения файла. 6 секунд в неделях
TEST(TestLogger, storage_6sec_in_weeks)
{
    //Обнулить результат операции
    bool result{};

    result = checkFileStorageTime(ProgramArguments::configLoggerFilePath_storage_6sec_in_weeks(), ProgramArguments::seconds_6_in_weeks());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/

//Проверить время хранения файла. Размер файла 100 байт
/*TEST(TestLogger, size_200_bytes)
{
    //Обнулить результат операции
    bool result{};

    //Удалить все файлы из директории лог-файлов
    std::filesystem::remove_all(ProgramArguments::logsFolderName());
    std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Изменить конфигурацию логгера. Создать новый файл для записи.
    kav::Logger::reset(ProgramArguments::configLoggerFilePath_size_200_bytes());

    waitFileWrite(ProgramArguments::waitFileWrite_micro_10());

    //Определить начальный размер файла
    int sizeBegin;
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        sizeBegin = currentDirectoryEntry.file_size();
    }

    //Удалить все файлы из директории лог-файлов
    std::filesystem::remove_all(ProgramArguments::logsFolderName());
    std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Количество итераций для заполнения нужного количества файлов
    int numberOfIterations{(ProgramArguments::size_200() * ProgramArguments::numberFiles_3()) / sizeBegin};

    //Если остаток остаётся
    if ((ProgramArguments::size_200() * ProgramArguments::numberFiles_3()) % sizeBegin)
    {
        //Добавить итерацию
        ++numberOfIterations;
    }

    for (int i{}; i < numberOfIterations; ++i)
    {
        std::cout << "\ni: " << i;
        //Изменить конфигурацию логгера. Создать новый файл для записи.
        kav::Logger::reset(ProgramArguments::configLoggerFilePath_size_200_bytes());
        //Изменить конфигурацию логгера. Создать новый файл для записи.
        kav::Logger::reset(ProgramArguments::configLoggerFilePath_size_200_bytes());
    }

    //Подсчитать количество лог-файлов в директории
    int filesNumber{};
    std::cout << '\n';
    waitFileWrite(ProgramArguments::waitFileWrite_micro_10());
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        ++filesNumber;std::cout << "currentDirectoryEntry: " << currentDirectoryEntry.path() << '\n';
    }

    //Если количество файлов равно требуемого
    if (filesNumber >= ProgramArguments::numberFiles_3() && filesNumber <= ProgramArguments::numberFiles_3() + 1)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/



//Проверить на невозможность создания дополнительного объекта.
/*TEST(TestLogger, additionalObjectFalse)
{
    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать дополнительный объект логирования событий
        kav::Logger logger2(ProgramArguments::configLoggerFilePath_size_200_bytes(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole_no());
    }
    catch (const kav::LoggerException& exception)
    {
        if (exception.what() == std::string("There should be only one object of the Logger class"))
        {
            result = true;
        }
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/

//Проверить на невозможность создания объекта при указании несуществующего файла конфигурации логгера
/*TEST(TestLogger, configLoggerFilePath_missing)
{
    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать дополнительный объект логирования событий
        kav::Logger logger2(ProgramArguments::configLoggerFilePath_missing(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole_no());
    }
    catch (const kav::LoggerException& exception)
    {
        if (exception.what() == std::string("This file is missing: " + ProgramArguments::configLoggerFilePath_missing()))
        {
            result = true;
        }
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить на невозможность создания объекта при указании файла конфигурации логгера несоответствующего шаблону
TEST(TestLogger, configLoggerFilePath_notMatch)
{
    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать дополнительный объект логирования событий
        kav::Logger logger3(ProgramArguments::configLoggerFilePath_notMatch(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole_no());
    }
    catch (const kav::LoggerException& exception)
    {
        if (exception.what() == std::string("The structure of this file does not match the required one: " + ProgramArguments::configLoggerFilePath_notMatch()))
        {
            result = true;
        }
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить на невозможность создания объекта при указании несуществующего файла конфигурации записи сообщений
TEST(TestLogger, configWriterMessageFilePath_missing)
{
    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать дополнительный объект логирования событий
        kav::Logger logger2(ProgramArguments::configLoggerFilePath_size_200_bytes(), ProgramArguments::configWriterMessageFilePath_missing(), ProgramArguments::launchConsole_no());
    }
    catch (const kav::LoggerException& exception)
    {
        if (exception.what() == std::string("This file is missing: " + ProgramArguments::configWriterMessageFilePath_missing()))
        {
            result = true;
        }
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить на невозможность создания объекта при указании файла конфигурации записи сообщений несоответствующего шаблону
TEST(TestLogger, configWriterMessageFilePath_notMatch)
{
    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать дополнительный объект логирования событий
        kav::Logger logger3(ProgramArguments::configLoggerFilePath_size_200_bytes(), ProgramArguments::configWriterMessageFilePath_notMatch(), ProgramArguments::launchConsole_no());
    }
    catch (const kav::LoggerException& exception)
    {
        if (exception.what() == std::string("The structure of this file does not match the required one: " + ProgramArguments::configWriterMessageFilePath_notMatch()))
        {
            result = true;
        }
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить на невозможность создания дополнительного объекта.
TEST(TestLogger, sendAndReceive)
{
    //Обнулить результат операции
    bool result{};

    //Удалить оставшуюся очередь (скорее всего, заблокированную)
    //boost::interprocess::message_queue::remove(ProgramArguments::nameOfQueue().c_str());

    kav::Logger::debug(ProgramArguments::messageForTest());

    std::string lastMessage{loggerMonitorExtern->getLastMessageReceived()};

        std::cout << lastMessage;

    /*if (last == ProgramArguments::messageForTest())
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/
