//
// Created by Alexander on 06.04.2025.
//



#include <string>

#include "windows.h"
#include <tlhelp32.h>

#include "boost/interprocess/ipc/message_queue.hpp"

#include "general.h"
#include "monitorSender.h"



void startMonitor(LPCSTR lpApplicationName)
{
    //Дополнительная информация
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    //Установить размеры структур
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );


    //Запустить независимый процесс
    if( !CreateProcess( lpApplicationName,   // No module name (use command line)
                        NULL,        // Command line
                        NULL,           // Process handle not inheritable
                        NULL,           // Thread handle not inheritable
                        FALSE,          // Set handle inheritance to FALSE
                        0,              // No creation flags
                        NULL,           // Use parent's environment block
                        NULL,           // Use parent's starting directory
                        &si,            // Pointer to STARTUPINFO structure
                        &pi )           // Pointer to PROCESS_INFORMATION structure
            )
    {
        //printf( "CreateProcess failed (%d).\n", GetLastError() );
        //return;
    }

    // Wait until child process exits.
    //WaitForSingleObject( pi.hProcess, INFINITE );

    //TODO проверить закрытие дескрипторов

    // Close process and thread handles.
    //CloseHandle( pi.hProcess );
    //CloseHandle( pi.hThread );

}

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

    std::cout << "search_engine:search_engine has started" << std::endl;

    //Процесс получения и вывода сообщений запущен. Очередь сообщений существует
    if (isProcessRun("search_engine_monitor.exe"))
    {
        std::cout << "search_engine:search_engine_monitor is already running"  << std::endl;
    }
    else
    {
        //Процесс получения и вывода сообщений не запущен. Удалить оставшуюся очередь сообщений (в любом случае)
        boost::interprocess::message_queue::remove("search_engine");
    }

    std::cout << "search_engine:open_or_create" << ": num_msg - " << mq.get_num_msg() << std::endl;

    //Запустить процесс получения и вывода сообщений (в любом случае). Этот процесс может быть запущен только в одном экземпляре
    // (регулируется именованным мьютексом).
    std::cout << "search_engine:search_engine_monitor is not running yet"  << std::endl;
    startMonitor(R"(C:\Users\Alexander\CLionProjects\search_engine\cmake-build-release\monitor\search_engine_monitor.exe)");
    std::cout << "search_engine:search_engine_monitor has started" << std::endl;

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

