//
// Created by Alexander on 14.04.2025.
//



#include <thread>

#include "windows.h"

#include "monitorReceiver.h"
#include "monitor.h"



int main()
{
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
