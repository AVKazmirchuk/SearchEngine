//
// Created by Alexander on 13.04.2025.
//



#include "logger.h"
#include "general.h"
#include "readWriteJSONFile.h"



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

void Logger::initialize(const std::string& configFilePath)
{
    //Создать JSON-объект конфигурации
    JSON configJSON = ReadWriteJSONFile::readJSONFile(configFilePath);

    //Инициализировать переменные
    initializeVariables(configJSON);

    //Настроить класс
    setupClass();
}