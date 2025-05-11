//
// Created by Alexander on 08.05.2025.
//



#include <fstream>

#include "logger.h"
#include "readWriteJSONFile.h"



void Logger::WriterMessage::writeToMonitor(const std::string& messageForOutput)
{
    //Отправить сообщение монитору (другому процессу)
    monitorSender->send(messageForOutput);
}

void Logger::WriterMessage::writeToFile(const std::string& messageForOutput)
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
    else
    {
        //Отправить сообщение монитору о невозможности открытия файла для записи
        monitorSender->send("Logger: This file cannot be opened for writing: " + file.string());
    }
}

void Logger::WriterMessage::processMessageContainer()
{
    //Каждое сообщение в контейнере сообщений
    for (const auto& message: messagesForOutput)
    {
        //Записать в файл
        writeToFile(message);

        //Отправить в монитор
        writeToMonitor(message);
    }
}

void Logger::WriterMessage::waitForMonitorToStart()
{
    //Если процесс не запущен
    if (!isProcessRun(fileNameOfMonitor.c_str()))
    {
        //Удалить сигнал-файл в любом случае (маркер запущенного процесса)
        std::filesystem::remove(indicatesMonitorStarting);

        //Запустить процесс получения и вывода сообщений (в любом случае). Этот процесс может быть запущен только в одном экземпляре
        // (регулируется именованным мьютексом).
        startMonitor(fileNameOfMonitor.c_str());

        //Ожидать запуска процесса (маркера запущенного процесса)
        do {
        } while (!std::filesystem::exists(indicatesMonitorStarting));
    }
}

void Logger::WriterMessage::initializeVariablesMonitorSender()
{
    //Параметры основного процесса и монитора

    //Имя очереди
    nameOfQueue = configMessageQueueJSON["messageQueue"]["nameOfQueue"];
    //Максимальное количество сообщений в очереди
    maxNumberOfMessages = configMessageQueueJSON["messageQueue"]["maxNumberOfMessages"];
    //Максимальный размер сообщения
    maxMessageSize = configMessageQueueJSON["messageQueue"]["maxMessageSize"];
    //Имя файла основной программы
    fileNameOfMainProgram = configMessageQueueJSON["messageQueue"]["fileNameOfMainProgram"];
    //Имя файла монитора
    fileNameOfMonitor = configMessageQueueJSON["messageQueue"]["fileNameOfMonitor"];
    //Имя консоли
    nameOfConsole = configMessageQueueJSON["messageQueue"]["nameOfConsole"];
    //Признак запуска монитора
    indicatesMonitorStarting = configMessageQueueJSON["messageQueue"]["indicatesMonitorStarting"];
}

void Logger::WriterMessage::initializeMonitorSender()
{
    //Создать JSON-объект конфигурации
    configMessageQueueJSON = ReadWriteJSONFile::readJSONFile(configMessageQueueFilePath);

    initializeVariablesMonitorSender();
}

void Logger::WriterMessage::run()
{

    initializeMonitorSender();

    //Создать объект монитора отправки сообщений
    MonitorSender monitorSenderItself(nameOfQueue,
                                maxNumberOfMessages,
                                maxMessageSize,
                                fileNameOfMonitor);

    monitorSender = &monitorSenderItself;

    //Ожидать запуска монитора (другого процесса)
    waitForMonitorToStart();

    //Пока не получено уведомление о завершении работы
    while (!pointerToLoggerObject->stopLogger.load())
    {
        //Ожидать сигнал о добавлении сообщения в контейнер сообщений
        std::unique_lock<std::mutex> uniqueLock(pointerToLoggerObject->mutReadWriteMessages);
        pointerToLoggerObject->cvPushMessage.wait(uniqueLock, [this]() { return pointerToLoggerObject->pushMessage; });

        //Копировать контейнер сообщений из основного потока
        messagesForOutput = pointerToLoggerObject->messages;
        //Очистить контейнер сообщений основного потока
        pointerToLoggerObject->messages.clear();
        //Сбросить подтверждение добавления сообщения в контейнер сообщений, так как сообщения приняты для обработки
        pointerToLoggerObject->pushMessage = false;

        //Разблокировать доступ к контейнеру сообщений из основного потока
        uniqueLock.unlock();

        //Обработать контейнер сообщений
        processMessageContainer();
    }

    //Перед завершением работы потока, проверить контейнер сообщений из основного потока и обработать, так как пока
    //поток обрабатывал очередь сообщений, основной поток мог ещё записать сообщения в контейнер сообщений. Это можно
    //делать без блокировок, так как получено уведомление о завершении работы из деструктора класса Logger.

    //Копировать контейнер сообщений из основного потока
    messagesForOutput = pointerToLoggerObject->messages;
    //Обработать очередь сообщений
    processMessageContainer();
}

void Logger::writeMessage(const std::string &in_configMessageQueueFilePath, Logger *pointerToLoggerObject)
{
    //Создать объект записи сообщений
    WriterMessage writerMessage(in_configMessageQueueFilePath, pointerToLoggerObject);

    //Записать информацию в файл и отправить информацию в монитор
    writerMessage.run();
}