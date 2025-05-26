//
// Created by Alexander on 20.04.2025.
//



#include <fstream>
#include "logger.h"
#include "checkFile.h"


bool Logger::isFileUsageTimeExceeded()
{
    //Создать объект для открытия файла
    std::ifstream inFile(file);

    //Файл не открывается для чтения
    if (!CheckFile::isFileOpenRead(inFile))//, file.string(), "bool Logger::isFileUsageTimeExceeded()"))
    {
        //Заменить файл
        return true;
    }

    //Объявить переменные
    std::string dateFirstEntry, timeFirstEntry;
    //Прочитать дату и время первой записи в файле
    inFile >> dateFirstEntry >> timeFirstEntry;

    //Закрыть файл
    inFile.close();

    std::tm tm{};
    std::istringstream iss{dateFirstEntry + ' ' + timeFirstEntry};
    iss >> std::get_time(&tm, configLogger.dateTimeFormat().c_str());
    std::time_t tt{std::mktime(&tm)};
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::from_time_t(tt)};

    //Вычислить интервал времени, в течение которого можно использовать текущий файл
    std::chrono::system_clock::duration usageTimeCurrent = std::chrono::system_clock::now() - tp;

    std::chrono::system_clock::duration usageTimeLimit = Weeks(configLogger.weeksUsage()) + Days(configLogger.daysUsage()) + Hours(configLogger.hoursUsage()) +
                                                         Minutes(configLogger.minutesUsage()) + Seconds(configLogger.secondsUsage());


    //Время использования текущего файла превышено
    if (usageTimeCurrent >= usageTimeLimit)
    {
        //Заменить файл
        return true;
    }

    //Использовать существующий
    return false;
}

void Logger::identifyFilesByLastModification(const std::string& directoryPath)
{
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

void Logger::identifyNewFile()
{
    std::time_t t{std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())};

    std::string ts(256,0);

    ts.resize(std::strftime(&ts[0], ts.size(), configLogger.fileNameFormat().c_str(), std::localtime(&t)));

    file = configLogger.filesDirectory() + ts + ".log";
}

void Logger::identifyFile(const std::string& directoryPath)
{
    //В директории файлов нет
    if (std::filesystem::is_empty(directoryPath))
    {
        //Заменить файл
        identifyNewFile();
        return;
    }

    //Определить файлы по последнему изменению
    identifyFilesByLastModification(directoryPath);

    //Размер файла больше допустимого
    if (std::filesystem::file_size(file) >= configLogger.fileSizeLimit())
    {
        //Заменить файл
        identifyNewFile();
    }

    //Время использования файла превышено
    if (isFileUsageTimeExceeded())
    {
        //Заменить файл
        identifyNewFile();
    }
}