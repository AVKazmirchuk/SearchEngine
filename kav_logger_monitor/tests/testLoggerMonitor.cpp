//
// Created by AKazmirchuk on 05.02.2026.
//



#include <future>
#include <thread>

#include "gtest/gtest.h"

#include "testGeneral.h"



//https://stackoverflow.com/questions/52539568/how-i-can-read-simply-console-output

void runLoggerMonitor(kav::LoggerMonitor& loggerMonitor)
{
    //Запустить монитор
    loggerMonitor.run();
}

//Проверить отправку и получение сообщения из очереди
bool checkSendAndReceiveMessage(const std::string &message)
{
    //Обнулить результат операции
    bool result{};

    //Удалить оставшуюся очередь (скорее всего, заблокированную)
    boost::interprocess::message_queue::remove(ProgramArguments::nameOfQueue().c_str());

    //Сначала надо запустить монитор. Если сделать наоборот - запись и чтение очереди не работает.

    //Создать объект класса логирования событий в монитор
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configLoggerMonitorFilePath());

    //Запустить монитор в другом потоке
    std::future<void> fut = std::async(&runLoggerMonitor, std::ref(loggerMonitor));

    //Создать объект очереди сообщений для отправки
    MonitorSender monitorSender(ProgramArguments::nameOfQueue(), ProgramArguments::maxNumberOfMessages_100(),
                                ProgramArguments::maxMessageSize_1024(), ProgramArguments::fileNameOfMonitor());

    //Отправить сообщение в монитор
    monitorSender.send(message);

    //Пока сообщение не получено
    while (loggerMonitor.getLastMessageReceived().empty())
    {
        //Ожидать получение сообщения в очереди
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    //Если сообщение принятое в мониторе совпадает с посланным
    if (loggerMonitor.getLastMessageReceived() == message)
    {
        //Результат теста верный
        result = true;
    }
    else
    {
        //Результат теста неверный
        result = false;
    }

    //Отправить сигнал об остановки монитора
    monitorSender.send(ProgramArguments::messageStop());

    //Дождаться завершения работы монитора
    fut.wait();

    //Вернуть результат
    return result;
}

//Проверить отправку и получение сообщения из консоли
bool checkSendAndReadFromConsole(const std::string &message)
{
    //Обнулить результат операции
    bool result{};

    //Удалить оставшуюся очередь (скорее всего, заблокированную)
    boost::interprocess::message_queue::remove(ProgramArguments::nameOfQueue().c_str());

    //Сначала надо запустить монитор. Если сделать наоборот - запись и чтение очереди не работает.

    //Создать объект класса логирования событий в монитор
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configLoggerMonitorFilePath());

    //Запустить монитор в другом потоке
    std::future<void> fut = std::async(&runLoggerMonitor, std::ref(loggerMonitor));

    //Создать объект очереди сообщений для отправки
    MonitorSender monitorSender(ProgramArguments::nameOfQueue(), ProgramArguments::maxNumberOfMessages_100(),
                                ProgramArguments::maxMessageSize_1024(), ProgramArguments::fileNameOfMonitor());

    //Начальное количество строк
    unsigned long beginNumberOfLines{getCursorPositionOfConsole().second};

    //Получить строку текущего момента времени
    std::string timePoint{timePointToString(std::chrono::system_clock::now())};

    //Сформировать окончательную строку для вывода на консоль
    std::string messageFinal{timePoint + " " + message};

    //Отправить сообщение в монитор
    monitorSender.send(messageFinal);

    //Ожидать запись сообщения в консоль
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    //Получить номер строки консоли, содержащей отправленное сообщение
    unsigned long numberOfLine{getLineNumber(messageFinal)};

    //Если номер строки не равен максимально возможному значению
    if (numberOfLine != std::numeric_limits<unsigned long>::max())
    {
        //Результат теста верный
        result = true;
    }
    else
    {
        //Результат теста неверный
        result = false;
    }

    //Отправить сигнал об остановки монитора
    monitorSender.send(ProgramArguments::messageStop());

    //Дождаться завершения работы монитора
    fut.wait();

    //Вернуть результат
    return result;
}

//Проверить отправку и получение сообщения из консоли
bool checkSendAndReadFromConsoleAttribute(const std::string &message, unsigned short color)
{
    //Обнулить результат операции
    bool result{};

    //Удалить оставшуюся очередь (скорее всего, заблокированную)
    boost::interprocess::message_queue::remove(ProgramArguments::nameOfQueue().c_str());

    //Сначала надо запустить монитор. Если сделать наоборот - запись и чтение очереди не работает.

    //Создать объект класса логирования событий в монитор
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configLoggerMonitorFilePath());

    //Запустить монитор в другом потоке
    std::future<void> fut = std::async(&runLoggerMonitor, std::ref(loggerMonitor));

    //Создать объект очереди сообщений для отправки
    MonitorSender monitorSender(ProgramArguments::nameOfQueue(), ProgramArguments::maxNumberOfMessages_100(),
                                ProgramArguments::maxMessageSize_1024(), ProgramArguments::fileNameOfMonitor());

    //Начальное количество строк
    unsigned long beginNumberOfLines{getCursorPositionOfConsole().second};

    //Получить строку текущего момента времени
    std::string timePoint{timePointToString(std::chrono::system_clock::now())};

    //Сформировать окончательную строку для вывода на консоль
    std::string messageFinal{timePoint + " " + message};

    //Отправить сообщение в монитор
    monitorSender.send(messageFinal);

    //Ожидать запись сообщения в консоль
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    //Получить номер строки консоли, содержащей отправленное сообщение
    unsigned long numberOfLine{getLineNumber(messageFinal)};

    //Если номер строки не равен максимально возможному значению
    if (numberOfLine != std::numeric_limits<unsigned long>::max())
    {
        if (getAttributeFromConsole(0, numberOfLine, messageFinal.size()) == std::vector<unsigned short>(messageFinal.size(), color))
        {
            //Результат теста верный
            result = true;
        }
        else
        {
            //Результат теста неверный
            result = false;
        }
    }
    else
    {
        //Результат теста неверный
        result = false;
    }

    //Отправить сигнал об остановки монитора
    monitorSender.send(ProgramArguments::messageStop());

    //Дождаться завершения работы монитора
    fut.wait();

    //Вернуть результат
    return result;
}



//Проверить отправку и получение сообщения из очереди уровня Debug
TEST(TestLoggerMonitor, createObjectFalse)
{
    //Обнулить результат операции
    bool result{};

    try
    {
        //Создать объект класса логирования событий в монитор
        kav::LoggerMonitor loggerMonitor(ProgramArguments::configLoggerMonitorFilePathNotExists());
    }
    catch (const kav::LoggerMonitorException& exception)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из очереди уровня Debug
TEST(TestLoggerMonitor, sendAndReceive_Debug)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Debug
    result = checkSendAndReceiveMessage(ProgramArguments::messageDebug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Debug
TEST(TestLoggerMonitor, sendAndReadFromConsole_Debug)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Debug
    result = checkSendAndReadFromConsole(ProgramArguments::messageDebug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Info
TEST(TestLoggerMonitor, sendAndReadFromConsole_Info)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Info
    result = checkSendAndReadFromConsole(ProgramArguments::messageInfo());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Warning
TEST(TestLoggerMonitor, sendAndReadFromConsole_Warning)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Warning
    result = checkSendAndReadFromConsole(ProgramArguments::messageWarning());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Error
TEST(TestLoggerMonitor, sendAndReadFromConsole_Error)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Error
    result = checkSendAndReadFromConsole(ProgramArguments::messageError());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Fatal
TEST(TestLoggerMonitor, sendAndReadFromConsole_Fatal)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Fatal
    result = checkSendAndReadFromConsole(ProgramArguments::messageFatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Logger
TEST(TestLoggerMonitor, sendAndReadFromConsole_Logger)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Logger
    result = checkSendAndReadFromConsole(ProgramArguments::messageLogger());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/



//Проверить отправку и получение сообщения из консоли уровня Debug (проверить аттрибут цвета)
TEST(TestLoggerMonitor, sendAndReadFromConsoleAttribute_Debug)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Debug
    result = checkSendAndReadFromConsoleAttribute(ProgramArguments::messageDebug(), ProgramArguments::messageDebugColor());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Info (проверить аттрибут цвета)
TEST(TestLoggerMonitor, sendAndReadFromConsoleAttribute_Info)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Info
    result = checkSendAndReadFromConsoleAttribute(ProgramArguments::messageInfo(), ProgramArguments::messageInfoColor());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Warning (проверить аттрибут цвета)
TEST(TestLoggerMonitor, sendAndReadFromConsoleAttribute_Warning)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Warning
    result = checkSendAndReadFromConsoleAttribute(ProgramArguments::messageWarning(), ProgramArguments::messageWarningColor());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Error (проверить аттрибут цвета)
TEST(TestLoggerMonitor, sendAndReadFromConsoleAttribute_Error)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Error
    result = checkSendAndReadFromConsoleAttribute(ProgramArguments::messageError(), ProgramArguments::messageErrorColor());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Fatal (проверить аттрибут цвета)
TEST(TestLoggerMonitor, sendAndReadFromConsoleAttribute_Fatal)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Fatal
    result = checkSendAndReadFromConsoleAttribute(ProgramArguments::messageFatal(), ProgramArguments::messageFatalColor());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить отправку и получение сообщения из консоли уровня Logger (проверить аттрибут цвета)
TEST(TestLoggerMonitor, sendAndReadFromConsoleAttribute_Logger)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Logger
    result = checkSendAndReadFromConsoleAttribute(ProgramArguments::messageLogger(), ProgramArguments::messageLoggerColor());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/

//Проверить отправку и получение сообщения из консоли уровня Logger (проверить аттрибут цвета)
TEST(TestLoggerMonitor, sendAndReadFromConsoleAttribute_LoggerError)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Logger
    result = checkSendAndReadFromConsoleAttribute(ProgramArguments::messageLogger(), ProgramArguments::messageErrorColor());

    //Проверить утверждение
    ASSERT_FALSE(result);
}