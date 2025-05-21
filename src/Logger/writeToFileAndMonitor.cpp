//
// Created by Alexander on 08.05.2025.
//



#include <fstream>

#include "logger.h"
#include "readWriteJSONFile.h"



void Logger::WriterMessage::writeToMonitor(const std::string& message)
{
    //Отправить сообщение монитору (другому процессу)
    monitorSender->send(message);
}

void Logger::WriterMessage::writeToFile(const std::string& message)
{
    //Создать объект для записи в файл
    std::ofstream outFile(Logger::ptrToLogger->file, std::ios::app);

    //Файл открывается для записи
    if (outFile.is_open())
    {
        //Записать сообщение в файл
        outFile << message << std::endl;

        //Закрыть файл
        outFile.close();
    }
    else
    {
        //Отправить сообщение монитору о невозможности открытия файла для записи
        monitorSender->send("Logger: This file cannot be opened for writing: " + Logger::ptrToLogger->file.string());
    }
}

void Logger::WriterMessage::processMessageContainer()
{
    //Каждое сообщение в контейнере сообщений
    for (const auto& message: messages)
    {
        //Записать в файл
        writeToFile(message);

        //Отправить в монитор
        writeToMonitor(message);
    }
}

void Logger::WriterMessage::startMonitor(LPCSTR lpApplicationName)
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

bool Logger::WriterMessage::isProcessRun(const char * const processName)
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

void Logger::WriterMessage::waitForMonitorToStart()
{
    //Если процесс не запущен
    if (!isProcessRun(fileNameOfMonitor.c_str()))
    {
        //Удалить сигнал-файл в любом случае (маркер запущенного процесса)
        std::filesystem::remove(indicatesMonitorStarting);

        //Запустить процесс получения и вывода сообщений (в любом случае). Этот процесс может быть запущен только в одном экземпляре
        // (регулируется именованным мьютексом).
        startMonitor(fileNameOfMonitor.c_str());

        //Ожидать запуска процесса (маркера запущенного процесса)
        do {
        } while (!std::filesystem::exists(indicatesMonitorStarting));
    }
}

void Logger::WriterMessage::initializeVariables()
{
    //Параметры основного процесса и монитора

    //Имя очереди
    nameOfQueue = configMessageQueueJSON["messageQueue"]["nameOfQueue"];
    //Максимальное количество сообщений в очереди
    maxNumberOfMessages = configMessageQueueJSON["messageQueue"]["maxNumberOfMessages"];
    //Максимальный размер сообщения
    maxMessageSize = configMessageQueueJSON["messageQueue"]["maxMessageSize"];
    //Имя файла основной программы
    fileNameOfMainProgram = configMessageQueueJSON["messageQueue"]["fileNameOfMainProgram"];
    //Имя файла монитора
    fileNameOfMonitor = configMessageQueueJSON["messageQueue"]["fileNameOfMonitor"];
    //Имя консоли
    nameOfConsole = configMessageQueueJSON["messageQueue"]["nameOfConsole"];
    //Признак запуска монитора
    indicatesMonitorStarting = configMessageQueueJSON["messageQueue"]["indicatesMonitorStarting"];
}

void Logger::WriterMessage::initialize()
{
    //Создать JSON-объект конфигурации
    configMessageQueueJSON = ReadWriteJSONFile::readJSONFile(configMessageQueueFilePath);

    //Инициализировать переменные
    initializeVariables();
}

void Logger::WriterMessage::run()
{

    //initializeMonitorSender();

    //Создать объект монитора отправки сообщений
    MonitorSender monitorSenderItself(nameOfQueue,
                                maxNumberOfMessages,
                                maxMessageSize,
                                fileNameOfMonitor);

    monitorSender = &monitorSenderItself;

    //Ожидать запуска монитора (другого процесса)
    waitForMonitorToStart();

    //Пока не получено уведомление о завершении работы
    while (!Logger::ptrToLogger->stopLogger.load())
    {
        //Ожидать сигнал о добавлении сообщения в контейнер сообщений
        std::unique_lock<std::mutex> uniqueLock(Logger::ptrToLogger->mutReadWriteMessages);
        Logger::ptrToLogger->cvPushMessage.wait(uniqueLock, [this]() { return Logger::ptrToLogger->pushMessage; });

        //Переместить сообщения из основного потока
        messages = std::move(Logger::ptrToLogger->messages);

        //Сбросить подтверждение добавления сообщения в контейнер сообщений, так как сообщения приняты для обработки
        Logger::ptrToLogger->pushMessage = false;

        //Разблокировать доступ к контейнеру сообщений из основного потока
        uniqueLock.unlock();

        //Обработать контейнер сообщений
        processMessageContainer();
    }

    //Перед завершением работы потока, проверить контейнер сообщений из основного потока и обработать, так как пока
    //поток обрабатывал очередь сообщений, основной поток мог ещё записать сообщения в контейнер сообщений. Это можно
    //делать без блокировок, так как получено уведомление о завершении работы из деструктора класса Logger.

    //Копировать контейнер сообщений из основного потока
    messages = Logger::ptrToLogger->messages;
    //Обработать очередь сообщений
    processMessageContainer();
}

void Logger::writeMessage()
{
    //Создать объект записи сообщений
    //WriterMessage writerMessage;

    //Записать информацию в файл и отправить информацию в монитор
    writerMessage.run();
}