//
// Created by Alexander on 09.04.2025.
//



#include <chrono>
#include <cstring>
#include <filesystem>
#include <fstream>

#include "general.h"
#include "logger.h"



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

std::string Logger::levelToString(Level level)
{
    switch (level)
    {
        case Level::L_DEBUG_L :
            return "DEBUG";
        case Level::L_INFO_L :
            return "INFO";
        case Level::L_WARNING_L :
            return "WARNING";
        case Level::L_ERROR_L :
            return "ERROR";
        case Level::L_FATAL_L :
            return "FATAL";
    }

    return "UNDEFINED";
}

std::string Logger::timePointToString(const std::chrono::system_clock::time_point& timePoint)
{
    std::time_t t{std::chrono::system_clock::to_time_t(timePoint)};

    std::string ts(256,0);

    ts.resize(std::strftime(&ts[0], ts.size(), dateTimeFormat.c_str(), std::localtime(&t)));

    return ts;
}

bool Logger::isFileUsageTimeExceeded()
{
    std::ifstream fileObj(file);

    if (!fileObj.is_open())
    {
        //TODO что-то делать
    }

    //Объявить переменные
    std::string dateFirstEntry, timeFirstEntry;
    //Прочитать дату и время первой записи в файле
    fileObj >> dateFirstEntry >> timeFirstEntry;

    //Закрыть файл
    fileObj.close();

    std::tm tm{};
    std::istringstream iss{dateFirstEntry + ' ' + timeFirstEntry};
    iss >> std::get_time(&tm, dateTimeFormat.c_str());
    std::time_t tt{std::mktime(&tm)};
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::from_time_t(tt)};

    //Вычислить интервал времени, в течение которого можно использовать текущий файл
    std::chrono::system_clock::duration usageTimeCurrent = std::chrono::system_clock::now() - tp;

    std::chrono::system_clock::duration usageTimeLimit = Weeks(weeksUsage) + Days(daysUsage) + Hours(hoursUsage) +
                                                        Minutes(minutesUsage) + Seconds(secondsUsage);


    //Время использования текущего файла превышено
    if (usageTimeCurrent >= usageTimeLimit)
    {
        //Заменить файл
        return true;
    }

    return false;
}

void Logger::identifyFilesByLastModification(const std::string& directoryPath)
{
    //Очистить контейнер пар пути и момента времени последнего изменения файла
    //logs.clear();

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

    using PairOfPathAndTimePoint = std::pair<std::filesystem::path, std::chrono::system_clock::time_point>;
    //Сортировать контейнер пар пути и момента времени последнего изменения файла
    std::stable_sort(logs.begin(), logs.end(),
                     [] (const PairOfPathAndTimePoint& a, const PairOfPathAndTimePoint& b)
                     {
                         //По возрастанию времени последнего изменения файла
                         return a.second < b.second;
                     });

    //Сделать файл для записи текущим
    file = logs.back().first;
}

std::filesystem::path Logger::getNewFile()
{
    std::time_t t{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};

    std::string ts(256,0);

    ts.resize(std::strftime(&ts[0], ts.size(), fileNameFormat.c_str(), std::localtime(&t)));

    return filesDirectory + ts + ".log";
}

void Logger::getFile(const std::string& directoryPath)
{
    //В директории файлов нет
    if (std::filesystem::is_empty(directoryPath))
    {
        //Заменить файл
        file = getNewFile();
    }

    //Определить файлы по последнему изменению
    identifyFilesByLastModification(directoryPath);

    //Размер файла больше допустимого
    if (std::filesystem::file_size(file) >= fileSizeLimit)
    {
        //Заменить файл
        file = getNewFile();
    }

    //Время использования файла превышено
    if (isFileUsageTimeExceeded())
    {
        //Заменить файл
        file = getNewFile();
    }

    //Вернуть последний (текущий) файл
    //file = logs.back().first;
}

void Logger::log(Level level, const std::string& message, const std::exception& exception)
{
    //Получить текущее время
    std::chrono::system_clock::time_point timeEvent{std::chrono::system_clock::now()};

    //Создать объект для записи
    std::ofstream outFile(file, std::ios::app);

    //Файл не открывается
    if (!outFile.is_open())
    {
        //TODO что-то делать
    }

    //Сообщение не содержит исключение
    if (!std::strcmp(exception.what(), "Exception-stub"))
    {
        //Записать сообщение в файл
        outFile << timePointToString(timeEvent) << "   " << levelToString(level) << ":   " <<
        message << std::endl;

        //Закрыть файл
        outFile.close();

        //Отправить сообщение другому процессу
        sendMessage(timePointToString(timeEvent) + "   " + levelToString(level) + ":   " + message);
    }
    else
        //Сообщение содержит исключение
    {
        //Записать сообщение в файл
        outFile << timePointToString(timeEvent) << "   " << levelToString(level) << ":   " <<
        "Exception: " << '"' << exception.what() << '"' << "   " << "Information: " << '"' << message << '"' << std::endl;

        //Закрыть файл
        outFile.close();

        //Отправить сообщение другому процессу
        sendMessage(timePointToString(timeEvent) + "   " + levelToString(level) + ":   " +
                                                 "Exception: " + '"' + exception.what() + '"' + "   " + "Information: " + '"' + message + '"');
    }
}