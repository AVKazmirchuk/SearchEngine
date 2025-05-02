//
// Created by Alexander on 09.04.2025.
//



#include <chrono>
#include <cstring>
#include <mutex>

#include "logger.h"



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

void Logger::log(Level level, const std::string& message, const std::exception& exception)
{
    //Получить текущее время
    std::chrono::system_clock::time_point timeEvent{std::chrono::system_clock::now()};

    //Сформировать сообщение для вывода
    std::string messageForOutput{generateMessageForOutput(level, message, exception, timeEvent)};

    //Заблокировать доступ к контейнеру сообщений из отдельного потока
    std::unique_lock<std::mutex> uniqueLock(selfObject->mutReadWriteMessages);

    //Добавить сообщение в контейнер сообщений
    messages.push_back(messageForOutput);
    //Установить подтверждение добавления сообщения
    selfObject->pushMessage = true;

    //Разблокировать доступ к контейнеру сообщений из отдельного потока логирования
    uniqueLock.unlock();

    //Сигнализировать о добавлении сообщения в контейнер сообщений
    selfObject->cvPushMessage.notify_one();
}
