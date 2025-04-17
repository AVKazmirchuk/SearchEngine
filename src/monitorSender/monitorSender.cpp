//
// Created by Alexander on 06.04.2025.
//



#include <string>

#include "windows.h"
#include <tlhelp32.h>

#include "boost/interprocess/ipc/message_queue.hpp"

#include "general.h"
#include "monitorSender.h"





void MonitorSender::send(const std::string& message)
{



    //TODO определиться с обработкой исключений
    try
    {
        //Отправить сообщение в очередь сообщений
        std::cout << "search_engine: before send: " << message << ": num_msg - " << mq.get_num_msg() << std::endl;
        mq.send(message.data(), message.size(), 0);
        std::cout << "search_engine: send: " << message << ": num_msg - " << mq.get_num_msg()  << std::endl;
    }
    catch(boost::interprocess::interprocess_exception& e)
    {
        std::cout << e.what();
    }
}

