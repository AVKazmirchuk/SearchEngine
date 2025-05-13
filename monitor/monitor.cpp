//
// Created by Alexander on 20.04.2025.
//



#include <iostream>
#include <string>
#include <fstream>
#include <thread>

#include "windows.h"

#include "nlohmann/json.hpp"
#include "boost/interprocess/ipc/message_queue.hpp"
#include "termcolor.h"

#include "monitor.h"
#include "monitorReceiver.h"
#include "readWriteJSONFile.h"



void LoggerMonitor::outputToConsole(const std::string& message)
{
    if (message.find("DEBUG") != std::string::npos) std::cout << termcolor::white << message << std::endl;
    else if (message.find("INFO") != std::string::npos) std::cout << termcolor::green << message << std::endl;
    else if (message.find("WARNING") != std::string::npos) std::cout << termcolor::yellow << message << std::endl;
    else if (message.find("ERROR") != std::string::npos) std::cout << termcolor::red << message << std::endl;
    else if (message.find("FATAL") != std::string::npos) std::cout << termcolor::red << message << std::endl;
    else if (message.find("Logger") != std::string::npos) std::cout << termcolor::cyan << message << std::endl;
}

void LoggerMonitor::initializeVariables(const JSON& configJSON)
{
    //Инициализировать переменные

    //Параметры основного процесса и монитора

    //Имя очереди
    nameOfQueue = configJSON["messageQueue"]["nameOfQueue"];
    //Максимальное количество сообщений в очереди
    maxNumberOfMessages = configJSON["messageQueue"]["maxNumberOfMessages"];
    //Максимальный размер сообщения
    maxMessageSize = configJSON["messageQueue"]["maxMessageSize"];
    //Имя файла основной программы
    fileNameOfMainProgram = configJSON["messageQueue"]["fileNameOfMainProgram"];
    //Имя файла монитора
    fileNameOfMonitor = configJSON["messageQueue"]["fileNameOfMonitor"];
    //Имя консоли
    nameOfConsole = configJSON["messageQueue"]["nameOfConsole"];
    //Признак запуска монитора
    indicatesMonitorStarting = configJSON["messageQueue"]["indicatesMonitorStarting"];

    queuesInUse.push_back(nameOfQueue);

}

void LoggerMonitor::initialize()
{
    //Создать JSON-объект конфигурации
    JSON configJSON = ReadWriteJSONFile::readJSONFile(configMessageQueueFilePath);

    //Инициализировать переменные
    initializeVariables(configJSON);
}

void LoggerMonitor::run()
{
    //Создать объект монитора получения сообщений
    MonitorReceiver monitorReceiver(nameOfQueue,
                                    maxNumberOfMessages,
                                    maxMessageSize,
                                    fileNameOfMainProgram);

    //Удалить сигнал-файл в любом случае (маркер запущенного процесса)
    std::filesystem::remove(indicatesMonitorStarting);
    //Создать сигнал-файл (маркер запущенного процесса)
    std::ofstream loggerMonitorAlreadyRunning(indicatesMonitorStarting);
    //Закрыть сигнал-файл
    loggerMonitorAlreadyRunning.close();

    //Установить заглавие консоли
    SetConsoleTitle(nameOfConsole.c_str());

    //Ожидать новых сообщений, получать и выводить их на монитор
    while (true)
    {
        //Получить сообщение
        std::string message{monitorReceiver.receive()};

        //Исключительная ситуация
        if (message == (nameOfQueue + "Stop"))
        {

                std::ofstream file{"LoggerMonitor.txt", std::ios::app};
                file << message << std::endl;

            break;
        }
        //Вывести сообщение на монитор
        outputToConsole(message);
    }
}

void LoggerMonitor::stop()
{
    for (auto& queue : queuesInUse)
    {
        std::cout << queue << std::endl;
        std::string messageStop{queue + "Stop"};
        std::cout << messageStop << std::endl;
        boost::interprocess::message_queue mq(boost::interprocess::open_only, queue.c_str());
        mq.send(messageStop.data(), messageStop.size(), 0);
    }
}
