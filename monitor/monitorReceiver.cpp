//
// Created by Alexander on 15.04.2025.
//



#include <iostream>

#include "monitorReceiver.h"



std::string MonitorReceiver::receive()
{
    //Подготовить данные для получения сообщения
    //Приоритет сообщения
    unsigned int priority{0};
    //Ожидаемое сообщение
    std::string message;
    //Задать размер оджидаемого сообщения
    message.resize(256);
    //Размер полученного сообщения
    boost::interprocess::message_queue::size_type recvd_size;

    //Получить сообщение из очереди сообщений. Ожидать, пока не появится новое сообщение
    mq.receive(&message[0], message.size(), recvd_size, priority);
    //Задать размер ожидаемого сообщения в соответствии с полученным
    message.resize(recvd_size);
    //Возвратить сообщение
    return message;
}