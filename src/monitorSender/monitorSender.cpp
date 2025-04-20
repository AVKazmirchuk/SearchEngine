//
// Created by Alexander on 06.04.2025.
//


#include <iostream>
#include <string>

#include "monitorSender.h"



void MonitorSender::send(const std::string& message)
{
    //Отправить сообщение в очередь сообщений. Ожидать, пока очередь сообщений не освободится для нового сообщения
    mq.send(message.data(), message.size(), 0);std::cout << "qwerty";
}

