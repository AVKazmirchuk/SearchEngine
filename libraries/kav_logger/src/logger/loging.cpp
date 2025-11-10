//
// Created by Alexander on 09.04.2025.
//



#include <chrono>
#include <cstring>
#include <mutex>

#include "kav/logger.h"



std::string kav::Logger::timePointToString(const std::chrono::system_clock::time_point& timePoint)
{
    //Преобразовать момент времени в объект времени POSIX
    std::time_t t{std::chrono::system_clock::to_time_t(timePoint)};

    //Задать размер строки
    std::string ts(256,0);

    //Преобразовать время в строку, и задать размер строки
    ts.resize(std::strftime(&ts[0], ts.size(), configLogger.dateTimeFormat().c_str(), std::localtime(&t)));

    //Вернуть строку времени
    return ts;
}

std::string kav::Logger::levelToString(Level level)
{
    //Вернуть строку уровня логирования в зависимости от значения перечисления
    switch (level)
    {
        case Level::debug :
            return "DEBUG";
        case Level::info :
            return "INFO";
        case Level::warning :
            return "WARNING";
        case Level::error :
            return "ERROR";
        case Level::fatal :
            return "FATAL";
    }

    //Вернуть неопределённую строку (никак не используется)
    return "UNDEFINED";
}

std::string kav::Logger::generateMessageForOutput(Level level, const std::string& message, const std::exception& exception, std::chrono::system_clock::time_point& timeEvent)
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

void kav::Logger::log(Level level, const std::string& message, const std::exception& exception)
{
    try
    {
        //Получить текущее время
        std::chrono::system_clock::time_point timeEvent{std::chrono::system_clock::now()};

        //Сформировать сообщение для вывода
        std::string messageForOutput{generateMessageForOutput(level, message, exception, timeEvent)};

        //Заблокировать доступ к контейнеру сообщений из отдельного потока
        std::unique_lock<std::mutex> uniqueLock(mutReadWriteMessages);

        //Добавить сообщение в контейнер сообщений
        messages.push_back(messageForOutput);
        //Установить подтверждение добавления сообщения
        pushMessage = true;

        //Разблокировать доступ к контейнеру сообщений из отдельного потока логирования
        uniqueLock.unlock();

        //Сигнализировать о добавлении сообщения в контейнер сообщений
        cvPushMessage.notify_one();
    }
    catch ()
    {

    }
}
