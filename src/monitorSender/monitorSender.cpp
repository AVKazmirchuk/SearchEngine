//
// Created by Alexander on 06.04.2025.
//


#include <iostream>
#include <string>

#include "monitorSender.h"

bool isProcessRun(const char * const processName)
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
}

void MonitorSender::send(const std::string& message)
{
    //Отправить сообщение в очередь сообщений. Ожидать, пока очередь сообщений не освободится для нового сообщения
    mq.send(message.data(), message.size(), 0);
}

