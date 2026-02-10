//
// Created by Alexander on 24.01.2026.
//



//#include "gtest/gtest.h"

#include "testGeneral.h"



int main()
{
    std::filesystem::copy("../../tests/resources/logger.json", "logger.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/messageQueue.json", "messageQueue.json", std::filesystem::copy_options::update_existing);
    std::filesystem::copy("../../tests/resources/logger_monitor.exe", "logger_monitor.exe", std::filesystem::copy_options::update_existing);
    std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Создать объект получения сообщения в очереди
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configWriterMessageFilePath_loggerTest());

    //Определить указатель для доступа к объекту из тестов
    loggerMonitorExtern = &loggerMonitor;

    //Запустить монитор в другом потоке
    std::future<void> fut = std::async(&kav::LoggerMonitor::run, loggerMonitorExtern);
    std::cout << "after kav::LoggerMonitor::run" << '\n';
    futureRun = &fut;

    //Создать объект логирования событий
    kav::Logger logger(ProgramArguments::configLoggerFilePath_size_200_bytes(), ProgramArguments::configWriterMessageFilePath_loggerTest(), ProgramArguments::queue_only());
    std::cout << "after logger" << '\n';

    std::string lastMessage{loggerMonitorExtern->getLastMessageReceived()};
    while (true)
    {
        std::cout << "lastMessage: " << lastMessage << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        std::string maybeLastMessage{loggerMonitorExtern->getLastMessageReceived()};
        std::cout << "maybeLastMessage: " << maybeLastMessage << '\n';
        if (maybeLastMessage == lastMessage)
        {
            break;
        }

        lastMessage = maybeLastMessage;
    }



    //Обнулить текущее количество сообщений
    loggerMonitorExtern->resetNumberOfReceivedMessages();


    std::atomic<bool> tmp{false};
    tmp.load();

    //Обнулить результат операции
    bool result{true};
    std::cout << "before for" << '\n';


//Послать сообщение
    kav::Logger::debug(std::string("test"));
    //Пока количество посланных сообщений не превисило максимального значения и текущий результат положительный
    for (int i{1}; i <= 10 && result; ++i)
    {
        //Определить текущий момент времени
        std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};

        //Преобразовать текущий момент времени в строку
        std::string strNow{timePointToString(now)};

        //Послать сообщение
        kav::Logger::debug(std::string("test") + " " + strNow);

        //Пока количество принятых сообщений не равно посланным
        /*while (loggerMonitorExtern->getNumberOfReceivedMessages() != i)
        {
            //Ожидать получение сообщения в очереди
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }*/

        //Ожидать получение сообщения в очереди
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        //Определить полученное сообщение
        std::string receivedMessage{loggerMonitorExtern->getLastMessageReceived()};

        std::cout << "receivedMessage: " << receivedMessage << ", strNow: " << strNow << '\n';

        //Определить текущий результат точной идентификацией полученного сообщения
        result = result && receivedMessage.find(strNow) != std::string::npos;

        receivedMessage = loggerMonitorExtern->getLastMessageReceived();

        std::cout << "receivedMessage: " << receivedMessage << ", strNow: " << strNow << '\n';
    }

    //Отправить сигнал об остановки монитора
    kav::Logger::debug("search_engine_testStop");

    //Дождаться завершения работы монитора
    futureRun->wait();

    //Запустить все тесты
    //::testing::InitGoogleTest();
    //return RUN_ALL_TESTS();
}