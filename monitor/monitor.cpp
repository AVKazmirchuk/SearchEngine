//
// Created by Alexander on 20.04.2025.
//



#include <iostream>
#include <string>
#include <fstream>

#include "windows.h"

#include "nlohmann/json.hpp"
#include "boost/interprocess/ipc/message_queue.hpp"
#include "termcolor.h"

#include "monitor.h"
#include "monitorReceiver.h"
#include "readWriteJSONFile.h"



BOOL WINAPI ConsoleCtrlEventHandler( DWORD dwCtrlType )
{
    switch (dwCtrlType)
    {
        case CTRL_C_EVENT:
        case CTRL_BREAK_EVENT:
            // Do nothing.
            // To prevent other potential handlers from
            // doing anything, return TRUE instead.
            return FALSE;

        case CTRL_CLOSE_EVENT:
            // Do your final processing here!
            MessageBox( NULL, "You clicked the 'X' in the console window! Ack!", "I'm melting!", MB_OK | MB_ICONINFORMATION );
            LoggerMonitor::stop();
            return FALSE;

        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            // Please be careful to read the implications of using
            // each one of these, and the applicability to your
            // code. Unless you are writing a Windows Service,
            // chances are you only need to pay attention to the
            // CTRL_CLOSE_EVENT type.
            return FALSE;
    }

    // If it gets this far (it shouldn't), do nothing.
    return FALSE;
}

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

    SetConsoleCtrlHandler( &ConsoleCtrlEventHandler, TRUE );

    //Ожидать новых сообщений, получать и выводить их на монитор
    while (true)
    {
        //Получить сообщение
        std::string message{monitorReceiver.receive()};
        std::cout << message << std::endl;
        //Исключительная ситуация
        if (message == (nameOfQueue + "Stop"))
        {
            std::cout << message << std::endl;
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
        std::string messageStop{queue + "Stop"};
        std::cout << messageStop << std::endl;
        boost::interprocess::message_queue mq(boost::interprocess::open_only, queue.c_str());
        mq.send(messageStop.data(), messageStop.size(), 0);
    }
}
