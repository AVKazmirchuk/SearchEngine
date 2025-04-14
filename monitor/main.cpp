//
// Created by Alexander on 14.04.2025.
//

#include <iostream>
#include <string>
#include <thread>

#include "boost/interprocess/ipc/message_queue.hpp"

#include "windows.h"

//Вывести сообщение на консоль
void outputToConsole(const std::string& message)
{
    std::cout << message << std::endl;
}

//Получить сообщение из очереди сообщений
void receiveMessage(boost::interprocess::message_queue& mq)
{
    //Подготовить данные для получения сообщения
    unsigned int priority{0};
    std::string message;
    message.resize(256);
    boost::interprocess::message_queue::size_type recvd_size;

    //Получить сообщение из очереди сообщений
    outputToConsole("search_engine_monitor:before receive: something: num_msg - " + std::to_string(mq.get_num_msg()));
    mq.receive(&message[0], message.size(), recvd_size, priority);
    message.resize(recvd_size);
    outputToConsole("search_engine_monitor:receive: " + message +  ": num_msg - " + std::to_string(mq.get_num_msg()));
}

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

    outputToConsole("search_engine_monitor:search_engine_monitor has started");

    //Открыть очередь сообщений
    boost::interprocess::message_queue mq(boost::interprocess::open_only, "search_engine");
    outputToConsole("search_engine_monitor:open_or_create: num_msg - " + std::to_string(mq.get_num_msg()));

    //Ожидать новых сообщений, получать и выводить их на консоль
    while (true)
    {
        receiveMessage(mq);
    }



    return 0;
}
