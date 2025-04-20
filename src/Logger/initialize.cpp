//
// Created by Alexander on 13.04.2025.
//



#include "windows.h"
#include <tlhelp32.h>

#include "logger.h"
#include "general.h"
#include "readWriteJSONFile.h"



void Logger::deleteFilesByRetentionPeriod()
{
    //Вычислить интервал времени, в течение которого можно хранить файл
    std::chrono::system_clock::duration storageTimeLimit = Weeks(weeksStorage) + Days(daysStorage) + Hours(hoursStorage) +
                                                           Minutes(minutesStorage) + Seconds(secondsStorage);
    //Для каждого элемента контейнера пар пути и момента времени последнего изменения файла, кроме последнего элемента
    //(последний файл должен остаться)
    for (auto it{logs.begin()}; it != logs.end() - 1; ++it)
    {
        //Определить текущий интервал хранения файла
        std::chrono::system_clock::duration storageTimeCurrent = std::chrono::system_clock::now() - it->second;
        //Текущий интервал хранения файла больше либо равно предельного
        if (storageTimeCurrent >= storageTimeLimit)
        {
            //Удалить текущий файл из директории
            std::filesystem::remove(it->first);
        }
    }
}

void Logger::startMonitor(LPCSTR lpApplicationName)
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

bool Logger::isProcessRun(const char * const processName)
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

void Logger::setupClass()
{
    //Получить файл для записи
    getFile(filesDirectory);

    //Удалить файлы по сроку хранения
    deleteFilesByRetentionPeriod();
}

void Logger::initializeVariables(const JSON& configJSON)
{
    //Инициализировать переменные

    //Интервалы времени хранения файла

    //Интервал времени хранения файла, количество недель
    weeksStorage = configJSON["storageTimeLimit"]["weeks"];
    //Интервал времени хранения файла, количество дней
    daysStorage = configJSON["storageTimeLimit"]["days"];
    //Интервал времени хранения файла, количество часов
    hoursStorage = configJSON["storageTimeLimit"]["hours"];
    //Интервал времени хранения файла, количество минут
    minutesStorage = configJSON["storageTimeLimit"]["minutes"];
    //Интервал времени хранения файла, количество секунд
    secondsStorage = configJSON["storageTimeLimit"]["seconds"];

    //Интервалы времени использования файла

    //Интервал времени использования файла, количество недель
    weeksUsage = configJSON["usageTimeLimit"]["weeks"];
    //Интервал времени использования файла, количество дней
    daysUsage = configJSON["usageTimeLimit"]["days"];
    //Интервал времени использования файла, количество часов
    hoursUsage = configJSON["usageTimeLimit"]["hours"];
    //Интервал времени использования файла, количество минут
    minutesUsage = configJSON["usageTimeLimit"]["minutes"];
    //Интервал времени использования файла, количество секунд
    secondsUsage = configJSON["usageTimeLimit"]["seconds"];

    //Формат даты и времени записи в файл
    dateTimeFormat = configJSON["dateTimeFormat"];
    //Формат имени файла
    fileNameFormat = configJSON["fileNameFormat"];
    //Предельный размер файла
    fileSizeLimit = configJSON["fileSizeLimit"];
    //Директория с файлами
    filesDirectory = configJSON["filesDirectory"];
}

void Logger::shouldDeleteMessageQueue()
{
    //Процесс получения и вывода сообщений запущен. Очередь сообщений существует
    if (isProcessRun("search_engine_monitor.exe"))
    {
        //std::cout << "search_engine:search_engine_monitor is already running"  << std::endl;
    }
    else
    {
        //Процесс получения и вывода сообщений не запущен. Удалить оставшуюся очередь сообщений (в любом случае)
        boost::interprocess::message_queue::remove("search_engine");
    }
}

void Logger::initialize(const std::string& configFilePath)
{
    //Определить необходимость удалить очередь
    shouldDeleteMessageQueue();

    //Запустить процесс получения и вывода сообщений (в любом случае). Этот процесс может быть запущен только в одном экземпляре
    // (регулируется именованным мьютексом).
    startMonitor(R"(C:\\Users\\Alexander\\CLionProjects\\search_engine\\cmake-build-release\\monitor\\search_engine_monitor.exe)");

    //Создать JSON-объект конфигурации
    JSON configJSON = ReadWriteJSONFile::readJSONFile(configFilePath);

    //Инициализировать переменные
    initializeVariables(configJSON);

    //Настроить класс
    setupClass();
}