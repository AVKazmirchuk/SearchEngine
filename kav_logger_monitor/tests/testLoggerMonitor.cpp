//
// Created by AKazmirchuk on 05.02.2026.
//



#include "gtest/gtest.h"

#include "testGeneral.h"



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

    //Запустить монитор
    loggerMonitor.run();



    //Проверить утверждение
    ASSERT_TRUE(result);
}