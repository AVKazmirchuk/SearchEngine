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
    std::ofstream outFile(Logger::file, std::ios::app);

    //Файл открывается для записи
    if (outFile.is_open())
    {
        //Записать сообщение в файл
        outFile << messageForOutput << std::endl;

        //Закрыть файл
        outFile.close();
    }
}

void Logger::writeToMonitor(const std::string& messageForOutput,MonitorSender& monitorSender)
{

    //Отправить сообщение другому процессу
    monitorSender.send(messageForOutput);

}

void Logger::processQueue(std::list<std::string> &messagesForOutput, MonitorSender& monitorSender)
{
    for (const auto& message: messagesForOutput)
    {

        //Записать информацию в файл
        writeToFile(message);

        std::cout << "qwerty" << std::endl;
        //Отправить информацию в монитор
        writeToMonitor(message, monitorSender);

        //messagesForOutput.pop_front();
        std::cout << "qwerty" << std::endl;
    }
}

void Logger::writeToFileAndMonitor()
{
    //Объект монитора отправки сообщений
    MonitorSender monitorSender;
    //std::cout << "qwerty100" << std::endl;

//std::cout << stopProgram.load() << std::endl;
    std::list<std::string> messagesForOutput;
    while (!stopProgram.load())
    {
        //std::cout << "qwerty1" << std::endl;

        std::cout << "bef" << std::endl;
        std::unique_lock<std::mutex> uniqueLock(mutContainerOfMessages);
        cvPushMessage.wait(uniqueLock, [this]() { return pushMessage.load(); });
        std::cout << "aft" << std::endl;

        messagesForOutput = messages;
        messages.clear();
        pushMessage.store(false);

        uniqueLock.unlock();

        processQueue(messagesForOutput, monitorSender);
        std::cout << "pop1" << std::endl;
        //std::cout << "qwerty2" << std::endl;
    }

    messagesForOutput = messages;
    processQueue(messagesForOutput, monitorSender);

    std::cout << messagesForOutput.size() << " pop2" << std::endl;

    //std::cout << "qwerty200" << std::endl;
    //threadStop.store(true);

    //cvThreadStop.notify_one();

}

void Logger::log(Level level, const std::string& message, const std::exception& exception)
{
    //Получить текущее время
    std::chrono::system_clock::time_point timeEvent{std::chrono::system_clock::now()};

    //Сформировать сообщение для вывода
    std::string messageForOutput{generateMessageForOutput(level, message, exception, timeEvent)};

    std::unique_lock<std::mutex> uniqueLock(self->mutContainerOfMessages);
    messages.push_back(messageForOutput);
    self->pushMessage.store(true);
    std::cout << "push" << std::endl;
    uniqueLock.unlock();

    self->cvPushMessage.notify_one();
}
