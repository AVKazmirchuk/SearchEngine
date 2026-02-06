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

    //Если сообщение принятые в мониторе совпадает с посланным
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
    unsigned long beginNumberOfLines{getSizeOfConsole().second};

    //Отправить сообщение в монитор
    monitorSender.send(message);

    //ПОка количество строк в консоле не увеличилось
    while (beginNumberOfLines == getSizeOfConsole().second)
    {
        //Ожидать запись сообщения в консоль
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    //Получить номер строки консоли, содержащей отправленное сообщение
    unsigned long numberOfLine{getLineNumber(message)};

    //Если номер строки не равен максимально возможному значению
    if (numberOfLine != std::numeric_limits<unsigned long >::max())
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

//Проверить отправку и получение сообщения из очереди уровня Debug
TEST(TestLoggerMonitor, sendAndReceive_Debug)
{
    //Обнулить результат операции
    bool result{};

    //Проверить отправку и получение сообщения уровня Debug
    result = checkSendAndReceiveMessage(ProgramArguments::messageDebug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/

//Проверить отправку и получение сообщения из консоли уровня Debug
TEST(TestLoggerMonitor, sendAndReadFromConsole_Debug)
{
    //Обнулить результат операции
    bool result{};

    //Получить строку текущего момента времени
    std::string timePoint{timePointToString(std::chrono::system_clock::now())};

    std::string messageFinal{timePoint + " " + ProgramArguments::messageDebug()};

    //Проверить отправку и получение сообщения уровня Debug
    result = checkSendAndReadFromConsole(messageFinal);

    //Проверить утверждение
    ASSERT_TRUE(result);
}//*/


/*
 * //monitorSender.send(ProgramArguments::messageDebug());
    //monitorSender.send(ProgramArguments::messageInfo());
    //monitorSender.send(ProgramArguments::messageWarning());
    //monitorSender.send(ProgramArguments::messageError());
    //monitorSender.send(ProgramArguments::messageFatal());
    //monitorSender.send(ProgramArguments::messageLogger());

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "getLineFromConsole: " << getLineFromConsole(0, 14) << '\n';
    std::cout << "getAttributeFromConsole:" << '\n';

    for (auto& elem : getAttributeFromConsole(0, 14))
    {
        std::cout << elem << " ";
    }
    std::cout << '\n';

    std::cout << "result: " << result;
 */