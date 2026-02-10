//
// Created by Alexander on 14.04.2025.
//



#include <filesystem>
#include <thread>

#include "windows.h"

#include "monitorReceiver.h"
#include "monitor.h"
#include "termcolor.h"



//Константы переменных
namespace Constants
{

    const std::string configLoggerMonitorFilePath{"messageQueue.json"};

    const std::string stop{"Stop"};
}

//Запустить монитор логирования
void runLoggerMonitor()
{
    //Создать объект класса логирования событий в монитор
    kav::LoggerMonitor loggerMonitor(Constants::configLoggerMonitorFilePath);

    //Запустить монитор
    loggerMonitor.run();
}

int main(int argc, char* argv[])
{

    //Защита от изменения имени файла (так как при инициализации очереди сообщений проверяется этот запущенный процесс)
    if (std::filesystem::path(argv[0]).filename() != "logger_monitor.exe")
    {
        return -1;
    }

    //Создать именованный мьютекс для ограничения количества запущенных экземпляров приложения (программа может быть запущена
    //только один раз)
    CreateMutexA(0, FALSE, "logger_monitor.exe");
    //Именованный мьютекс уже существует
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
        //Завершить программу
        return EXIT_FAILURE;
    }

    //Запустить монитор логирования
    try
    {
        runLoggerMonitor();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what();
    }

    return EXIT_SUCCESS;
}
