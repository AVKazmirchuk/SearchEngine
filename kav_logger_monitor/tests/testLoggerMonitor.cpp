//
// Created by AKazmirchuk on 05.02.2026.
//



#include <future>
#include <thread>

#include "gtest/gtest.h"

#include "testGeneral.h"



void runLoggerMonitor(kav::LoggerMonitor& loggerMonitor)
{
    //Запустить монитор
    loggerMonitor.run();
}



TEST(TestLoggerMonitor, anyTest)
{
    //Обнулить результат операции
    bool result{};

    //Удалить оставшуюся очередь (скорее всего, заблокированную)
    boost::interprocess::message_queue::remove(ProgramArguments::nameOfQueue().c_str());
std::cout << "Очередь удалилась";
    //Объект очереди сообщений для отправки
    MonitorSender monitorSender(ProgramArguments::nameOfQueue(), ProgramArguments::maxNumberOfMessages_100(),
                                          ProgramArguments::maxMessageSize_1024(), ProgramArguments::fileNameOfMonitor());

    monitorSender.send(ProgramArguments::message());



    //Создать объект класса логирования событий в монитор
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configLoggerMonitorFilePath());

    std::future<void> future = std::async(&runLoggerMonitor, std::ref(loggerMonitor));

    /*while (loggerMonitor.getLastMessageReceived().empty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }*/


    if (loggerMonitor.getLastMessageReceived() == ProgramArguments::message())
    {
        result = true;
    }

    monitorSender.send(ProgramArguments::messageStop());

    future.get();

    //Проверить утверждение
    ASSERT_TRUE(result);
}