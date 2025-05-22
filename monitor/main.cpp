//
// Created by Alexander on 14.04.2025.
//



#include <filesystem>
#include <thread>

#include "windows.h"

#include "monitorReceiver.h"
#include "monitor.h"
#include "termcolor.h"





//Вспомогательная функция запуска самой программы. Вынесено отдельно, для корректной обработки исключений
void auxiliary()
{
    //Создать объект класса логирования событий в монитор
    LoggerMonitor loggerMonitor(constants::configLoggerMonitorFilePath);

    loggerMonitor.run();
}

int main(int argc, char* argv[])
{

    /*std::cout << termcolor::grey << "termcolor::grey:" << std::endl;
    std::cout << termcolor::red << "termcolor::red:" << std::endl;
    std::cout << termcolor::green << "termcolor::green:" << std::endl;
    std::cout << termcolor::yellow << "termcolor::yellow:" << std::endl;
    std::cout << termcolor::blue << "termcolor::blue:" << std::endl;
    std::cout << termcolor::magenta << "termcolor::magenta:" << std::endl;
    std::cout << termcolor::cyan << "termcolor::cyan:" << std::endl;
    std::cout << termcolor::white << "termcolor::white:" << std::endl;

    std::cout << termcolor::bright_grey << "termcolor::bright_grey:" << std::endl;
    std::cout << termcolor::bright_red << "termcolor::bright_red:" << std::endl;
    std::cout << termcolor::bright_green << "termcolor::bright_green:" << std::endl;
    std::cout << termcolor::bright_yellow << "termcolor::bright_yellow:" << std::endl;
    std::cout << termcolor::bright_blue << "termcolor::bright_blue:" <<  std::endl;
    std::cout << termcolor::bright_magenta << "termcolor::bright_magenta:" << std::endl;
    std::cout << termcolor::bright_cyan << "termcolor::bright_cyan:" << std::endl;
    std::cout << termcolor::bright_white << "termcolor::bright_white:" << std::endl;

std::getchar();*/

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



/*
    //Создать объект класса логирования событий в монитор
    LoggerMonitor loggerMonitor(constants::configMessageQueueFilePath);

    loggerMonitor.run();
*/

    //Запустить саму программу
    try
    {
        auxiliary();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what();
    }

    return 0;
}
