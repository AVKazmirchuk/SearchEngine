//
// Created by Alexander on 15.04.2025.
//



#include <iostream>

#include "monitorReceiver.h"



//Вывести сообщение на консоль
void outputToConsole(const std::string& message)
{
    std::cout << message << std::endl;
}

void MonitorReceiver::receive()
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