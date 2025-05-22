//
// Created by Alexander on 21.05.2025.
//



#include "logger.h"
#include "readWriteJSONFile.h"



void Logger::ConfigLogger::initialize()
{
    //Создать JSON-объект конфигурации
    configLoggerJSON = ReadWriteJSONFile::readJSONFile(configLoggerFilePath);

    //Интервалы времени хранения файла

    //Интервал времени хранения файла, количество недель
    weeksStorageTime = configLoggerJSON["storageTimeLimit"]["weeks"];
    //Интервал времени хранения файла, количество дней
    daysStorageTime = configLoggerJSON["storageTimeLimit"]["days"];
    //Интервал времени хранения файла, количество часов
    hoursStorageTime = configLoggerJSON["storageTimeLimit"]["hours"];
    //Интервал времени хранения файла, количество минут
    minutesStorageTime = configLoggerJSON["storageTimeLimit"]["minutes"];
    //Интервал времени хранения файла, количество секунд
    secondsStorageTime = configLoggerJSON["storageTimeLimit"]["seconds"];

    //Интервалы времени использования файла

    //Интервал времени использования файла, количество недель
    weeksUsageTime = configLoggerJSON["usageTimeLimit"]["weeks"];
    //Интервал времени использования файла, количество дней
    daysUsageTime = configLoggerJSON["usageTimeLimit"]["days"];
    //Интервал времени использования файла, количество часов
    hoursUsageTime = configLoggerJSON["usageTimeLimit"]["hours"];
    //Интервал времени использования файла, количество минут
    minutesUsageTime = configLoggerJSON["usageTimeLimit"]["minutes"];
    //Интервал времени использования файла, количество секунд
    secondsUsageTime = configLoggerJSON["usageTimeLimit"]["seconds"];

    //Формат даты и времени записи в файл
    dateTimeFmt = configLoggerJSON["dateTimeFormat"];
    //Формат имени файла
    fileNameFmt = configLoggerJSON["fileNameFormat"];
    //Предельный размер файла
    fileSizeLmt = configLoggerJSON["fileSizeLimit"];
    //Директория с файлами
    filesDir = configLoggerJSON["filesDirectory"];
}

void Logger::WriterMessage::ConfigWriterMessage::initialize()
{
    //Создать JSON-объект конфигурации
    configWriterMessageJSON = ReadWriteJSONFile::readJSONFile(configWriterMessageFilePath);

    //Имя очереди
    nameOfQueueValue = configWriterMessageJSON["messageQueue"]["nameOfQueue"];
    //Максимальное количество сообщений в очереди
    maxNumberOfMessagesValue = configWriterMessageJSON["messageQueue"]["maxNumberOfMessages"];
    //Максимальный размер сообщения
    maxMessageSizeValue = configWriterMessageJSON["messageQueue"]["maxMessageSize"];
    //Имя файла основной программы
    fileNameOfMainProgramValue = configWriterMessageJSON["messageQueue"]["fileNameOfMainProgram"];
    //Имя файла монитора
    fileNameOfMonitorValue = configWriterMessageJSON["messageQueue"]["fileNameOfMonitor"];
    //Имя консоли
    nameOfConsoleValue = configWriterMessageJSON["messageQueue"]["nameOfConsole"];
    //Признак запуска монитора
    indicatesMonitorStartingValue = configWriterMessageJSON["messageQueue"]["indicatesMonitorStarting"];
}