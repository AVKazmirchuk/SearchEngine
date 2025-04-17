//
// Created by Alexander on 14.04.2025.
//



#include <iostream>
#include <string>
#include <thread>

#include "windows.h"

#include "monitorReceiver.h"



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

    std::cout << "search_engine_monitor:search_engine_monitor has started" << std::endl;
    //std::cout << boost::interprocess::message_queue::remove("search_engine") << std::endl;
    //Открыть очередь сообщений
    //boost::interprocess::message_queue mq(boost::interprocess::open_only, "search_engine");
    //Создать объект монитора получения сообщений
    MonitorReceiver monitorReceiver;

    //outputToConsole("search_engine_monitor:open_or_create: num_msg - " + std::to_string(monitorReceiver.get().get_num_msg()));

    //Ожидать новых сообщений, получать и выводить их на консоль
    while (true)
    {
        //Получить сообщение
        monitorReceiver.receive();
    }

    return 0;
}
