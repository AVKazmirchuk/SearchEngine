//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"



void SearchEngine::ConfigSearchEngine::initialize()
{
    //Создать JSON-объект конфигурации
    configJSON = ReadWriteJSONFile::readJSONFile(configFilePath, configTemplate);
    requestsJSON = ReadWriteJSONFile::readJSONFile(requestsFilePath, requestsTemplate);

    //Интервалы времени хранения файла

    //Интервал времени хранения файла, количество недель
    //weeksStorageTime = configLoggerJSON["storageTimeLimit"]["weeks"];
    //Интервал времени хранения файла, количество дней
    //daysStorageTime = configLoggerJSON["storageTimeLimit"]["days"];
    //Интервал времени хранения файла, количество часов
    //hoursStorageTime = configLoggerJSON["storageTimeLimit"]["hours"];
    //Интервал времени хранения файла, количество минут
    //minutesStorageTime = configLoggerJSON["storageTimeLimit"]["minutes"];
    //Интервал времени хранения файла, количество секунд
    //secondsStorageTime = configLoggerJSON["storageTimeLimit"]["seconds"];

    //Интервалы времени использования файла

    //Интервал времени использования файла, количество недель
    //weeksUsageTime = configLoggerJSON["usageTimeLimit"]["weeks"];
    //Интервал времени использования файла, количество дней
    //daysUsageTime = configLoggerJSON["usageTimeLimit"]["days"];
    //Интервал времени использования файла, количество часов
    //hoursUsageTime = configLoggerJSON["usageTimeLimit"]["hours"];
    //Интервал времени использования файла, количество минут
    //minutesUsageTime = configLoggerJSON["usageTimeLimit"]["minutes"];
    //Интервал времени использования файла, количество секунд
    //secondsUsageTime = configLoggerJSON["usageTimeLimit"]["seconds"];

    //Формат даты и времени записи в файл
    //dateTimeFmt = configLoggerJSON["dateTimeFormat"];
    //Формат имени файла
    //fileNameFmt = configLoggerJSON["fileNameFormat"];
    //Предельный размер файла
    //fileSizeLmt = configLoggerJSON["fileSizeLimit"];
    //Директория с файлами
    //filesDir = configLoggerJSON["filesDirectory"];
}