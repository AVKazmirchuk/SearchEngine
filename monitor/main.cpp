//
// Created by Alexander on 14.04.2025.
//


#include <iostream>
#include <filesystem>
#include <thread>

#include "windows.h"

#include "monitorReceiver.h"
#include "monitor.h"



int main(int argc, char* argv[])
{
    //Защита от изменения имени файла (так как при инициализации очереди сообщений проверяется этот запущенный процесс)
    if (std::filesystem::path(argv[0]).filename() != "search_engine_monitor.exe")
    {
        //std::cout << argv[0] << std::endl;
        //std::cout << std::filesystem::path(argv[0]).filename();
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

    //Создать объект монитора получения сообщений
    MonitorReceiver monitorReceiver;

    if (!MonitorReceiver::isProcessAlreadyRunning)
    {
        for (std::string messageTest{}; messageTest != "search_engine-test";) {
            monitorReceiver.send("search_engine_monitor-test");

            try {
                messageTest = monitorReceiver.try_receive();
            }
            catch (const std::exception &exception) { ;
            }
        }
    }


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
