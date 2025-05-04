//
// Created by Alexander on 14.04.2025.
//



#include <filesystem>
#include <fstream>
#include <thread>

#include "windows.h"

#include "monitorReceiver.h"
#include "monitor.h"



int main(int argc, char* argv[])
{
    //Защита от изменения имени файла (так как при инициализации очереди сообщений проверяется этот запущенный процесс)
    if (std::filesystem::path(argv[0]).filename() != "search_engine_monitor.exe")
    {
        return -1;
    }

    //Создать именованный мьютекс для ограничения количества запущенных экземпляров приложения (программа может быть запущена
    //только один раз)
    CreateMutexA(0, FALSE, "search_engine_monitor.exe");
    //Именованный мьютекс уже существует
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        //Завершить программу
        return -1;
    }

    //Установить заглавие консоли
    SetConsoleTitle("Logger Monitor");

    //Создать объект класса логирования событий в монитор
    LoggerMonitor loggerMonitor(constants::configLoggerFilePath);

    //Создать объект монитора получения сообщений
    MonitorReceiver monitorReceiver(LoggerMonitor::nameOfQueue,
                                    maxNumberOfMessages,
                                    maxMessageSize,
                                    fileNameOfMa);

    //Удалить сигнал-файл в любом случае (маркер запущенного процесса)
    std::filesystem::remove(R"(C:\Windows\Temp\search_engine_monitor)");
    //Создать сигнал-файл (маркер запущенного процесса)
    std::ofstream loggerMonitorAlreadyRunning(R"(C:\Windows\Temp\search_engine_monitor)");
    //Закрыть сигнал-файл
    loggerMonitorAlreadyRunning.close();

    //Ожидать новых сообщений, получать и выводить их на монитор
    while (true)
    {
        //Получить сообщение
        std::string message{monitorReceiver.receive()};
        //Вывести сообщение на монитор
        outputToConsole(message);
    }

    return 0;
}
