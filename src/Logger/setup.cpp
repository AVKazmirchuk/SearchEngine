//
// Created by Alexander on 08.05.2025.
//



#include <thread>

#include "windows.h"

#include "logger.h"
#include "general.h"
#include "fileOperation.h"



void Logger::deleteFilesByRetentionPeriod()
{
    //Контейнер пар пути и момента времени последнего изменения файла не пустой
    if (!logs.empty())
    {
        //Вычислить интервал времени, в течение которого можно хранить файл
        std::chrono::system_clock::duration storageTimeLimit = Weeks(configLogger.weeksStorage()) + Days(configLogger.daysStorage()) + Hours(configLogger.hoursStorage()) +
                                                               Minutes(configLogger.minutesStorage()) + Seconds(configLogger.secondsStorage());

        //Для каждого элемента контейнера пар пути и момента времени последнего изменения файла, кроме последнего элемента
        //(последний файл должен остаться)
        for (auto it{logs.begin()}; it != logs.end() - 1; ++it) {
            //Определить текущий интервал хранения файла
            std::chrono::system_clock::duration storageTimeCurrent = std::chrono::system_clock::now() - it->second;
            //Текущий интервал хранения файла больше либо равно предельного
            if (storageTimeCurrent >= storageTimeLimit) {
                //Удалить текущий файл из директории
                std::filesystem::remove(it->first);
            }
        }
    }
}

void Logger::setup()
{
    //Определить файл для записи
    identifyFile(configLogger.filesDirectory());

    //Удалить файлы по сроку хранения
    deleteFilesByRetentionPeriod();
}
