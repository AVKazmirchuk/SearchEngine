//
// Created by Alexander on 09.04.2025.
//



#include <chrono>
#include <cstring>
#include <fstream>
#include <mutex>

#include "logger.h"




std::string Logger::levelToString(Level level)
{
    //Вернуть строку уровня логирования в зависимости от значения перечисления
    switch (level)
    {
        case Level::L_DEBUG_L :
            return "DEBUG";
        case Level::L_INFO_L :
            return "INFO";
        case Level::L_WARNING_L :
            return "WARNING";
        case Level::L_ERROR_L :
            return "ERROR";
        case Level::L_FATAL_L :
            return "FATAL";
    }

    //Вернуть неопределённую строку (никак не используется)
    return "UNDEFINED";
}

std::string Logger::timePointToString(const std::chrono::system_clock::time_point& timePoint)
{
    //Преобразовать момент времени в объект времени POSIX
    std::time_t t{std::chrono::system_clock::to_time_t(timePoint)};

    //Задать размер строки
    std::string ts(256,0);

    //Преобразовать время в строку, и задать размер строки
    ts.resize(std::strftime(&ts[0], ts.size(), dateTimeFormat.c_str(), std::localtime(&t)));

    //Вернуть строку времени
    return ts;
}

std::string Logger::generateMessageForOutput(Level level, const std::string& message, const std::exception& exception, std::chrono::system_clock::time_point& timeEvent)
{
    //Сообщение не содержит исключение
    if (!std::strcmp(exception.what(), "Exception-stub"))
    {
        return timePointToString(timeEvent) + "   " + levelToString(level) + ":   " + message;
    }

    //Сообщение содержит исключение
    return timePointToString(timeEvent) + "   " + levelToString(level) + ":   " +
                                    "Exception: " + '"' + exception.what() + '"' + "   " + "Information: " + '"' +
                                    message +
                                    '"';
}

void Logger::writeToFile(const std::string& messageForOutput)
{
    //Создать объект для записи в файл
    std::ofstream outFile(file, std::ios::app);

    //Файл открывается для записи
    if (outFile.is_open())
    {
        //Записать сообщение в файл
        outFile << messageForOutput << std::endl;

        //Закрыть файл
        outFile.close();
    }
}

void Logger::writeToMonitor(const std::string& messageForOutput)
{
    if (monitorSender)
    {
        //Отправить сообщение другому процессу
        monitorSender->send(messageForOutput);
    }
}

void Logger::writeToFileAndMonitor(MonitorSender* in_monitorSender)
{
    if (in_monitorSender)
    {
        monitorSender = in_monitorSender;

        if (!isProcessRun("search_engine_monitor.exe"))
        {
            std::filesystem::remove(R"(C:\Windows\Temp\search_engine_monitor)");

            //Запустить процесс получения и вывода сообщений (в любом случае). Этот процесс может быть запущен только в одном экземпляре
            // (регулируется именованным мьютексом).
            startMonitor(
                    R"(C:\\Users\\Alexander\\CLionProjects\\search_engine\\cmake-build-release\\monitor\\search_engine_monitor.exe)");

            std::size_t numLoop{};
            do
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++numLoop;
            } while (!std::filesystem::exists(R"(C:\Windows\Temp\search_engine_monitor)"));

            std::cout << numLoop << std::endl;
        }
    }

    while (!stopProgram.load())
    {
        std::cout << "qwerty1" << std::endl;
        std::unique_lock<std::mutex> uniqueLock(mutContainerOfMessages);
        cvPushMessage.wait(uniqueLock, []() { return pushMessage.load(); });
        if (!messageToForward.empty())
        {
            std::string messageForOutput{messageToForward};

            messageToForward = "";

            pushMessage.store(false);

            uniqueLock.unlock();


            //Записать информацию в файл
            writeToFile(messageForOutput);


            //Отправить информацию в монитор
            writeToMonitor(messageForOutput);
            std::cout << "qwerty" << std::endl;
        }
        std::cout << "qwerty2" << std::endl;
    }

    //threadStop.store(true);

    //cvThreadStop.notify_one();

}

void Logger::log(Level level, const std::string& message, const std::exception& exception)
{
    //Получить текущее время
    std::chrono::system_clock::time_point timeEvent{std::chrono::system_clock::now()};

    //Сформировать сообщение для вывода
    std::string messageForOutput{generateMessageForOutput(level, message, exception, timeEvent)};

    std::unique_lock<std::mutex> uniqueLock(mutContainerOfMessages);
    messageToForward = messageForOutput;
    uniqueLock.unlock();

    pushMessage.store(true);
    cvPushMessage.notify_one();

}
