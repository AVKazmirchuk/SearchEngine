//
// Created by Alexander on 15.04.2025.
//



#include "monitorReceiver.h"



std::string kav::MonitorReceiver::receive(const boost::interprocess::message_queue::size_type maxMessageSize)
{
    //Подготовить данные для получения сообщения

    //Приоритет сообщения
    unsigned int priority{0};
    //Ожидаемое сообщение
    std::string message;
    //Задать размер оджидаемого сообщения
    message.resize(maxMessageSize);
    //Размер полученного сообщения
    boost::interprocess::message_queue::size_type recvd_size;

    //Получить сообщение из очереди сообщений. Ожидать, пока не появится новое сообщение
    mq.receive(&message[0], message.size(), recvd_size, priority);
    //Задать размер ожидаемого сообщения в соответствии с полученным
    message.resize(recvd_size);
    //Возвратить сообщение
    return message;
}

/*bool kav::MonitorReceiver::RemoveMessageQueue::isProcessRun(const char * const processName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    Process32First(hSnapshot, &pe);

    bool result{};
    while (true) {
        if (strcmp(pe.szExeFile, processName) == 0)
        {
            result = true;
            break;
        }
        if (!Process32Next(hSnapshot, &pe))
        {
            result = false;
            break;
        }
    }

    CloseHandle(hSnapshot);

    return result;
}*/

