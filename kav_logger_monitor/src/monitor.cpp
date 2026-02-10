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
#include "kav/operationFileAndJSON.h"



//Константы переменных
namespace Constants
{

    const std::string stop{"Stop"};
}



void kav::LoggerMonitor::outputToConsole(const std::string& message)
{
    //В зависимости от уровня логирования вывести сообщения своими цветами
    if (message.find("DEBUG") != std::string::npos) std::cout << termcolor::white << message << std::endl;
    else if (message.find("INFO") != std::string::npos) std::cout << termcolor::green << message << std::endl;
    else if (message.find("WARNING") != std::string::npos) std::cout << termcolor::yellow << message << std::endl;
    else if (message.find("ERROR") != std::string::npos) std::cout << termcolor::red << message << std::endl;
    else if (message.find("FATAL") != std::string::npos) std::cout << termcolor::bright_red << message << std::endl;
    else if (message.find("LOGGER") != std::string::npos) std::cout << termcolor::cyan << message << std::endl;
}

void kav::LoggerMonitor::run()
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
        std::string message = monitorReceiver.receive(configLoggerMonitor.maxMessageSize());

        //Исключительная ситуация
        if (message == (configLoggerMonitor.nameOfQueue() + Constants::stop))
        {
            break;
        }

        //Вывести сообщение на монитор
        outputToConsole(message);

        //Заблокировать доступ к последнему сообщению
        std::lock_guard<std::mutex> lg(mutReadWriteLastMessage);

        lastMessage = message;
    }
}

void kav::LoggerMonitor::stop()
{
    //Для каждой очереди
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

BOOL WINAPI kav::LoggerMonitor::ConsoleCtrlEventHandler(DWORD dwCtrlType)
{
    //В зависимости от события
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

void kav::LoggerMonitor::ConfigLoggerMonitor::initialize()
{
    //Прочитать файл конфигурации монитора
    std::pair<JSON, kav::ErrorCode> tmp = kav::OperationFileAndJSON::readJSONFile(configLoggerMonitorFilePath);
    //Если чтение завершилось ошибкой
    if (tmp.second != kav::ErrorCode::no_error)
    {
        //Выбросить исключение. Будет обработано выше в главной функции
        throw LoggerMonitorException(tmp.second, configLoggerMonitorFilePath);
    }
    else
    {
        //Проверить JSON-структуру на соответствие шаблону
        if (auto tmpError{OperationFileAndJSON::checkJSONStructureMatch(tmp.first, TemplatesJSONObjects::configLoggerMonitorJSONTemplate())}; tmpError != ErrorCode::no_error)
        {
            throw LoggerMonitorException(tmpError, configLoggerMonitorFilePath);
        }
    }

    //Создать JSON-объект конфигурации
    configLoggerMonitorJSON = std::move(tmp.first);

    //std::pair<JSON, kav::ErrorCode> tmp{kav::OperationFileAndJSON::readJSONFile(filePath, callingFunction)};
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