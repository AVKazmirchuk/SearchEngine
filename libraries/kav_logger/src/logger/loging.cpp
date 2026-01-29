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

    //Преобразовать момент времени в секунды
    std::chrono::system_clock::time_point nowSeconds{std::chrono::time_point_cast<std::chrono::seconds>(timePoint)};

    //Получить наносекунды
    std::chrono::nanoseconds nanoseconds{timePoint - nowSeconds};

    //Преобразовать наносекунды в строку
    std::stringstream ss4;
    ss4 << nanoseconds.count();
    std::string strNanosecondsCount;
    ss4 >> strNanosecondsCount;

    //Вернуть строку времени
    return ts + '.' + strNanosecondsCount;
}

std::string kav::Logger::levelToString(Level level)
{
    //Вернуть строку уровня логирования в зависимости от значения перечисления
    switch (level)
    {
        case Level::logger :
            return "LOGGER";
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
    //Модифицированное сообщение
    std::string modifiedMessage{message};

    //Пока последний символ в сообщении пробел или таб
    while (modifiedMessage.back() == ' ' || modifiedMessage.back() == '\t')
    {
        //Удалить его
        modifiedMessage.pop_back();
    }

    //Если последний символ точка
    if (modifiedMessage.back() == '.')
    {
        //Удалить его
        modifiedMessage.pop_back();
    }

    //Сообщение не содержит исключение
    if (!std::strcmp(exception.what(), "Exception-stub"))
    {
        return timePointToString(timeEvent) + "   " + levelToString(level) + ":   " + modifiedMessage + ".";
    }

    //Сообщение содержит исключение
    return timePointToString(timeEvent) + "   " + levelToString(level) + ":   " +
                                    "Exception: " + '"' + exception.what() + '"' + ". " + "   " + "Information: " + '"' +
            modifiedMessage +
                                    '"' + ".";
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

        //Сообщение для потока записи отправлено в контейнер. Другой поток будет записывать в файл и в монитор
        recordingMessage.store(true);

        //Сигнализировать о добавлении сообщения в контейнер сообщений
        cvPushMessage.notify_one();
    }
    catch (std::exception& e)
    {
        //Будет обработано в функциях выше
        throw LoggerException(e.what());
    }
}
