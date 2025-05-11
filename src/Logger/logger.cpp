//
// Created by Alexander on 01.04.2025.
//



#include "logger.h"
#include "readWriteJSONFile.h"



void Logger::debug(const std::string& message)
{
    debug(message, ExceptionStub());
}

void Logger::debug(const std::string& message, const std::exception& exception)
{
    log(Level::L_DEBUG_L, message, exception);
}

void Logger::info(const std::string& message)
{
    info(message, ExceptionStub());
}

void Logger::info(const std::string& message, const std::exception& exception)
{
    log(Level::L_INFO_L, message, exception);
}

void Logger::warning(const std::string& message)
{
    warning(message, ExceptionStub());
}

void Logger::warning(const std::string& message, const std::exception& exception)
{
    log(Level::L_WARNING_L, message, exception);
}

void Logger::error(const std::string& message)
{
    error(message, ExceptionStub());
}

void Logger::error(const std::string& message, const std::exception& exception)
{
    log(Level::L_ERROR_L, message, exception);
}

void Logger::fatal(const std::string& message)
{
    fatal(message, ExceptionStub());
}

void Logger::fatal(const std::string& message, const std::exception& exception)
{
    log(Level::L_FATAL_L, message, exception);
}

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