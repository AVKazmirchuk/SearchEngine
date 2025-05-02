//
// Created by Alexander on 02.05.2025.
//



#include <fstream>

#include "logger.h"



void Logger::writeToMonitor(const std::string& messageForOutput,MonitorSender& monitorSender)
{
    //Отправить сообщение монитору (другому процессу)
    monitorSender.send(messageForOutput);
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

void Logger::processQueue(std::list<std::string> &messagesForOutput, MonitorSender& monitorSender)
{
    //Каждое сообщение в текущей очереди сообщений
    for (const auto& message: messagesForOutput)
    {
        //Записать в файл
        writeToFile(message);

        //Отправить в монитор
        writeToMonitor(message, monitorSender);
    }
}

void Logger::waitForMonitorToStart()
{
    //Если процесс не запущен
    if (!isProcessRun("search_engine_monitor.exe"))
    {
        //Удалить сигнал-файл в любом случае (маркер запущенного процесса)
        std::filesystem::remove(R"(C:\Windows\Temp\search_engine_monitor)");

        //Запустить процесс получения и вывода сообщений (в любом случае). Этот процесс может быть запущен только в одном экземпляре
        // (регулируется именованным мьютексом).
        startMonitor(
                R"(C:\\Users\\Alexander\\CLionProjects\\search_engine\\cmake-build-release\\monitor\\search_engine_monitor.exe)");

        //Ожидать запуска процесса (маркера запущенного процесса)
        do {
        } while (!std::filesystem::exists(R"(C:\Windows\Temp\search_engine_monitor)"));
    }
}

void Logger::writeToFileAndMonitor()
{
    //Создать объект монитора отправки сообщений
    MonitorSender monitorSender;

    //Ожидать запуска монитора (другого процесса)
    waitForMonitorToStart();

    //Текущая очередь сообщений (локальная для этого потока)
    std::list<std::string> messagesForOutput;

    //Пока не получено уведомление о завершении работы
    while (!stopLogger.load())
    {
        //Ожидать сигнал о добавлении сообщения в контейнер сообщений
        std::unique_lock<std::mutex> uniqueLock(mutReadWriteMessages);
        cvPushMessage.wait(uniqueLock, [this]() { return pushMessage; });

        //Копировать контейнер сообщений из основного потока
        messagesForOutput = messages;
        //Очистить контейнер сообщений основного потока
        messages.clear();
        //Сбросить подтверждение добавления сообщения в контейнер сообщений, так как сообщения приняты для обработки
        pushMessage = false;

        //Разблокировать доступ к контейнеру сообщений из основного потока
        uniqueLock.unlock();

        //Обработать очередь сообщений
        processQueue(messagesForOutput, monitorSender);
    }

    //Перед завершением работы потока, проверить контейнер сообщений из основного потока и обработать, так как пока
    //поток обрабатывал очередь сообщений, основной поток мог ещё записать сообщения в контейнер сообщений. Это можно
    //делать без блокировок, так как получено уведомление о завершении работы из деструктора класса.

    //Копировать контейнер сообщений из основного потока
    messagesForOutput = messages;
    //Обработать очередь сообщений
    processQueue(messagesForOutput, monitorSender);
}