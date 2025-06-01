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

void LoggerMonitor::run()
{
    //Удалить сигнал-файл в любом случае (маркер запущенного процесса)
    std::filesystem::remove(configLoggerMonitor.indicatesMonitorStarting());
    //Создать сигнал-файл (маркер запущенного процесса)
    std::ofstream loggerMonitorAlreadyRunning(configLoggerMonitor.indicatesMonitorStarting());
    //Закрыть сигнал-файл
    loggerMonitorAlreadyRunning.close();

    //Установить заглавие консоли
    SetConsoleTitle(configLoggerMonitor.nameOfConsole().c_str());

    //Ожидать новых сообщений, получать и выводить их на монитор
    while (true)
    {
        //Получить сообщение
        std::string message{monitorReceiver.receive()};

        //Исключительная ситуация
        if (message == (configLoggerMonitor.nameOfQueue() + "Stop"))
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
        //Создать сообщение о завершении работы
        std::string messageStop{queue + "Stop"};
        //Открыть существующую текущую очередь сообщений
        boost::interprocess::message_queue mq(boost::interprocess::open_only, queue.c_str());
        //Послать в очередь сообщение о заверешении работы
        mq.send(messageStop.data(), messageStop.size(), 0);
    }
}

BOOL WINAPI LoggerMonitor::ConsoleCtrlEventHandler(DWORD dwCtrlType)
{
    switch (dwCtrlType)
    {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
        case CTRL_CLOSE_EVENT:
            //Завершить работу
            LoggerMonitor::stop();
            //Ждать максимум, сколько позволяет ОС, для завершения работы приложения
            std::this_thread::sleep_for(std::chrono::seconds(15));

            return TRUE;

        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            //Для служб Windows
            return FALSE;
    }

    //Если обработка событий приведёт сюда - оставить обработчик по умолчанию
    return FALSE;
}

void LoggerMonitor::ConfigLoggerMonitor::initialize()
{
    //Создать JSON-объект конфигурации
    configLoggerMonitorJSON = ReadWriteJSONFile::readJSONFile(configLoggerMonitorFilePath);
    std::cout << "qwerty" << std::endl;
    //Имя очереди
    nameOfQueueValue = configLoggerMonitorJSON["messageQueue"]["nameOfQueue"];
    //Максимальное количество сообщений в очереди
    maxNumberOfMessagesValue = configLoggerMonitorJSON["messageQueue"]["maxNumberOfMessages"];
    //Максимальный размер сообщения
    maxMessageSizeValue = configLoggerMonitorJSON["messageQueue"]["maxMessageSize"];
    //Имя файла основной программы
    fileNameOfMainProgramValue = configLoggerMonitorJSON["messageQueue"]["fileNameOfMainProgram"];
    //Имя файла монитора
    fileNameOfMonitorValue = configLoggerMonitorJSON["messageQueue"]["fileNameOfMonitor"];
    //Имя консоли
    nameOfConsoleValue = configLoggerMonitorJSON["messageQueue"]["nameOfConsole"];
    //Признак запуска монитора
    indicatesMonitorStartingValue = configLoggerMonitorJSON["messageQueue"]["indicatesMonitorStarting"];
}