//
// Created by Alexander on 20.04.2025.
//



#include <fstream>

#include "kav/detail/constants.h"
#include "kav/logger.h"



bool kav::Logger::isFileUsageTimeExceeded()
{
    //Момент времени последнего изменения текущего файла
    std::chrono::system_clock::time_point tp{};

    //Прочитать первую строку лог-файла
    auto tmp = OperationFileAndJSON::readFirstLineFromTextFile(file.string());

    //Если при чтении ошибок не было
    if (tmp.second == ErrorCode::no_error)
    {
        //Получить момент времени из строки
        tp = getTimePointFromString(tmp.first);
    }
    else
    {
        //Обработать ошибку чтения лог-файла. В этой функции избыточно
        handleErrorReadingLogFile(file);
    }

    //Вычислить интервал времени, в течение которого можно использовать текущий файл
    std::chrono::system_clock::duration usageTimeCurrent = std::chrono::system_clock::now() - tp;

    //Вычислить интервал времени, до которого можно использовать текущий файл
    std::chrono::duration<double, std::ratio<1>> usageTimeLimit = Weeks(configLogger.weeksUsage()) + Days(configLogger.daysUsage()) + Hours(configLogger.hoursUsage()) +
                                                         Minutes(configLogger.minutesUsage()) + Seconds(configLogger.secondsUsage());

    //Если время использования текущего файла превышено
    if (usageTimeCurrent >= usageTimeLimit)
    {
        //Заменить файл
        return true;
    }

    //Использовать существующий
    return false;
}

void kav::Logger::identifyFilesByLastModification()
{
    using PairOfPathAndTimePoint = std::pair<std::filesystem::path, std::chrono::system_clock::time_point>;

    //Сортировать контейнер пар пути и момента времени последнего изменения файла
    std::sort(logs.begin(), logs.end(),
                     [] (const PairOfPathAndTimePoint& a, const PairOfPathAndTimePoint& b)
                     {
                         //По возрастанию времени последнего изменения файла
                         return a.second < b.second;
                     });

    //Сделать файл для записи текущим
    file = logs.back().first;

    //std::cout << '\n' << "identifyFilesByLastModification" << '\n';
    //std::cout << "logs size: " << logs.size() << '\n';
    /*for (auto& elem : logs)
    {
        std::cout << "path: " << elem.first << ", " << "time: " << elem.second << '\n';
    }*/
}

void kav::Logger::identifyNewFile()
{
    //Получить текущий момент времени
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};
    //Преобразовать текущее значение времени в нужный формат
    std::time_t t{std::chrono::system_clock::to_time_t(now)};
    //Подготовить переменную
    std::string ts(256, 0);
    //Определить имя файла по формату даты и времени
    ts.resize(std::strftime(&ts[0], ts.size(), configLogger.fileNameFormat().c_str(), std::localtime(&t)));

    //Получить наносекунды
    std::string strNanosecondsCount{converTimePointToNanoseconds(now)};

    //Получить имя файла с наносекундами
    file = configLogger.filesDirectory() + ts + '_' + strNanosecondsCount + ".log";

    //std::cout << '\n' << "identifyNewFile" << '\n';
    //std::cout << "current log: " << file;
    logger(Constants::messageNewFileCreate());
}

void kav::Logger::identifyFile(const std::string& directoryPath)
{
    //В директории файлов нет
    if (std::filesystem::is_empty(directoryPath))
    {
        //std::cout << '\n' << "identifyFile (is_empty)" << '\n';
        //std::cout << "\nDirectory is empty\n";
        //Заменить файл
        identifyNewFile();
        return;
    }

    //Определить файлы по последнему изменению
    identifyFilesByLastModification();
//std::cout << "after identifyFilesByLastModification" << '\n';
    //Размер файла больше допустимого
    if (std::filesystem::file_size(file) >= configLogger.fileSizeLimit())
    {
        //std::cout << '\n' << "identifyFile (file_size)" << '\n';
        //std::cout << std::filesystem::file_size(file) << "\n";
        //Заменить файл
        identifyNewFile();
        return;
    }

    //Время использования файла превышено
    if (isFileUsageTimeExceeded())
    {
        //Заменить файл
        identifyNewFile();
        return;
    }


}