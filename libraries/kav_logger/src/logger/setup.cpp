//
// Created by Alexander on 08.05.2025.
//



#include <thread>

#include "kav/logger.h"
#include "kav/detail/types.h"



void kav::Logger::deleteFilesByRetentionPeriod(const std::string& directoryPath)
{
    //Очистить контейнер пар пути и момента времени последнего изменения файла
    logs.clear();

    //Определить файл в директории по последнему логированию
    //Для каждого файла в директории
    for (auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        //Определить момент времени последнего изменения файла
        auto lastWriteTime = std::filesystem::last_write_time(entry.path());

        //Преобразовать момент времени последнего изменения файла в нужный тип
        std::time_t ttCurrent = to_time_t(lastWriteTime);
        std::chrono::system_clock::time_point tpCurrent{std::chrono::system_clock::from_time_t(ttCurrent)};

        //Добавить в контейнер пару пути и момента времени последнего изменения файла
        logs.emplace_back(entry.path(), tpCurrent);
    }

    //Контейнер, пар пути и момента времени последнего изменения файла, не пустой
    if (!logs.empty())
    {
        //Вычислить интервал времени, в течение которого можно хранить файл
        std::chrono::duration<double, std::ratio<1>> storageTimeLimit = Weeks(configLogger.weeksStorage()) + Days(configLogger.daysStorage()) + Hours(configLogger.hoursStorage()) +
                                                               Minutes(configLogger.minutesStorage()) + Seconds(configLogger.secondsStorage());
        //std::cout << " storageTimeLimit: " << storageTimeLimit;
        //Для каждого элемента контейнера пар пути и момента времени последнего изменения файла, кроме последнего элемента
        //(последний файл должен остаться)
        for (auto it{logs.begin()}; it != logs.end(); ++it)
        {
            //Определить текущий интервал хранения файла
            std::chrono::system_clock::duration storageTimeCurrent = std::chrono::system_clock::now() - it->second;
            //std::cout << " storageTimeCurrent: " << storageTimeCurrent;
            //Текущий интервал хранения файла больше либо равно предельного
            if (storageTimeCurrent >= storageTimeLimit)
            {
                //Удалить текущий файл из директории
                std::filesystem::remove(it->first);
            }
        }
    }
}

void kav::Logger::setup()
{
    //Удалить файлы по сроку хранения
    deleteFilesByRetentionPeriod(configLogger.filesDirectory());

    //Определить файл для записи
    identifyFile(configLogger.filesDirectory());

    //Записать сообщение уровня logger
    logger(Constants::messageLoggerStarted());
}
