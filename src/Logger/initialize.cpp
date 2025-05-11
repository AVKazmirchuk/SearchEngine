//
// Created by Alexander on 08.05.2025.
//



#include <thread>

#include "windows.h"

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

void Logger::setupClass()
{
    //Определить файл для записи
    identifyFile(filesDirectory);

    //Удалить файлы по сроку хранения
    deleteFilesByRetentionPeriod();
}

void Logger::initializeVariables()
{
    //Инициализировать переменные

    //Интервалы времени хранения файла

    //Интервал времени хранения файла, количество недель
    weeksStorage = configLoggerJSON["storageTimeLimit"]["weeks"];
    //Интервал времени хранения файла, количество дней
    daysStorage = configLoggerJSON["storageTimeLimit"]["days"];
    //Интервал времени хранения файла, количество часов
    hoursStorage = configLoggerJSON["storageTimeLimit"]["hours"];
    //Интервал времени хранения файла, количество минут
    minutesStorage = configLoggerJSON["storageTimeLimit"]["minutes"];
    //Интервал времени хранения файла, количество секунд
    secondsStorage = configLoggerJSON["storageTimeLimit"]["seconds"];

    //Интервалы времени использования файла

    //Интервал времени использования файла, количество недель
    weeksUsage = configLoggerJSON["usageTimeLimit"]["weeks"];
    //Интервал времени использования файла, количество дней
    daysUsage = configLoggerJSON["usageTimeLimit"]["days"];
    //Интервал времени использования файла, количество часов
    hoursUsage = configLoggerJSON["usageTimeLimit"]["hours"];
    //Интервал времени использования файла, количество минут
    minutesUsage = configLoggerJSON["usageTimeLimit"]["minutes"];
    //Интервал времени использования файла, количество секунд
    secondsUsage = configLoggerJSON["usageTimeLimit"]["seconds"];

    //Формат даты и времени записи в файл
    dateTimeFormat = configLoggerJSON["dateTimeFormat"];
    //Формат имени файла
    fileNameFormat = configLoggerJSON["fileNameFormat"];
    //Предельный размер файла
    fileSizeLimit = configLoggerJSON["fileSizeLimit"];
    //Директория с файлами
    filesDirectory = configLoggerJSON["filesDirectory"];
}

void Logger::initialize()
{
    //Создать JSON-объект конфигурации
    configLoggerJSON = ReadWriteJSONFile::readJSONFile(configLoggerFilePath);

    //Инициализировать переменные
    initializeVariables();

    //Настроить класс
    setupClass();
}
