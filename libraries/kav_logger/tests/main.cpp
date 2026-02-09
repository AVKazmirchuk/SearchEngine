//
// Created by Alexander on 24.01.2026.
//



#include "gtest/gtest.h"

#include "testGeneral.h"

void runLoggerMonitor(kav::LoggerMonitor& loggerMonitor)
{
    //Запустить монитор
    loggerMonitor.run();
}

int main()
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Удалить оставшуюся очередь (скорее всего, заблокированную)
    //boost::interprocess::message_queue::remove(ProgramArguments::nameOfQueue().c_str());

std::cout << "before loggerMonitor" << '\n';
    //Создать объект получения сообщения в очереди
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configWriterMessageFilePath_loggerTest());

    //Запустить монитор в другом потоке
    //std::future<void> fut = std::async(&kav::LoggerMonitor::run, &loggerMonitor);

    //Запустить монитор в другом потоке
    std::future<void> fut = std::async(&runLoggerMonitor, std::ref(loggerMonitor));

    loggerMonitorExtern = &loggerMonitor;
std::this_thread::sleep_for(std::chrono::seconds(1));
    //Создать объект логирования событий
    kav::Logger logger(ProgramArguments::configLoggerFilePath_size_200_bytes(), ProgramArguments::configWriterMessageFilePath_loggerTest(), ProgramArguments::queue_only());

    //Ожидать
    waitFileWrite(ProgramArguments::waitFileWrite_micro_10());

    kav::Logger::debug(ProgramArguments::messageForTest());
std::cout << "before while" << '\n';
    //Пока сообщение не получено
    /*while (loggerMonitor.getLastMessageReceived().empty())
    {
        //Ожидать получение сообщения в очереди
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }*/

    //Если сообщение принятое в мониторе совпадает с посланным
    /*if (loggerMonitor.getLastMessageReceived() == ProgramArguments::messageForTest())
    {
        //Результат теста верный
        result = true;
    }
    else
    {
        //Результат теста неверный
        result = false;
    }*/

    std::string lastMessage{loggerMonitorExtern->getLastMessageReceived()};

    std::cout << lastMessage;


    //Запустить все тесты
    //::testing::InitGoogleTest();
    //return RUN_ALL_TESTS();
}