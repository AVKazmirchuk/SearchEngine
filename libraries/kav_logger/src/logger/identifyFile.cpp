//
// Created by Alexander on 20.04.2025.
//



#include <fstream>

#include "kav/detail/constants.h"
#include "kav/logger.h"



bool kav::Logger::isFileUsageTimeExceeded()
{
    //Создать объект для открытия файла
    std::ifstream inFile(file);

    //Файл не открывается для чтения
    if (!inFile.is_open())
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

    //Преобразовать строки даты и времени, прочитанных из файла, в удобный формат времени для дальнейшего использования
    std::tm tm{};
    std::istringstream iss{dateFirstEntry + ' ' + timeFirstEntry};
    iss >> std::get_time(&tm, configLogger.dateTimeFormat().c_str());
    std::time_t tt{std::mktime(&tm)};
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::from_time_t(tt)};

    //Определить подстроку с наносекундами
    std::string strNanoseconds{timeFirstEntry.substr(timeFirstEntry.find('.') + 1)};

    //Получить из подстроки наносекунды
    std::chrono::nanoseconds nanoseconds{std::stoull(strNanoseconds)};

    //Получить момент времени с наносекундами
    tp += nanoseconds;

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

    std::cout << '\n' << "identifyFilesByLastModification" << '\n';
    for (auto& elem : logs)
    {
        std::cout << "path: " << elem.first << ", " << "time: " << elem.second << '\n';
    }
}

void kav::Logger::identifyNewFile()
{
    //Получить текущий момент времени
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};
    //Преобразовать текущее значение времени в нужный формат
    std::time_t t{std::chrono::system_clock::to_time_t(now)};
    //Подготовить переменную
    std::string ts(256,0);
    //Определить имя файла по формату даты и времени
    ts.resize(std::strftime(&ts[0], ts.size(), configLogger.fileNameFormat().c_str(), std::localtime(&t)));
    //Задать временное имя файла
    //std::filesystem::path fileTmp = configLogger.filesDirectory() + ts + ".log";

    //if (fileTmp == file)
    //{
        //Преобразовать момент времени в секунды
        std::chrono::system_clock::time_point nowSeconds{std::chrono::time_point_cast<std::chrono::seconds>(now)};

        //Получить наносекунды
        std::chrono::nanoseconds nanoseconds{now - nowSeconds};

        //Преобразовать наносекунды в строку
        std::stringstream ss4;
        ss4 << nanoseconds.count();
        std::string strNanosecondsCount;
        ss4 >> strNanosecondsCount;



        //Получить имя файла с наносекундами
        file = configLogger.filesDirectory() + ts + '_' + strNanosecondsCount + ".log";
    //}
    //else
    //{
    //    //Получить имя файла без наносекунд (по шаблону)
    //    file = configLogger.filesDirectory() + ts + ".log";
    //}
    std::cout << '\n' << "identifyNewFile" << '\n';
    std::cout << "current log: " << file;
    logger(Constants::messageNewFileCreate());
}

void kav::Logger::identifyFile(const std::string& directoryPath)
{
    //В директории файлов нет
    if (std::filesystem::is_empty(directoryPath))
    {
        std::cout << '\n' << "identifyFile (is_empty)" << '\n';
        std::cout << "\nDirectory is empty\n";
        //Заменить файл
        identifyNewFile();
        return;
    }

    //Определить файлы по последнему изменению
    identifyFilesByLastModification();

    //Размер файла больше допустимого
    if (std::filesystem::file_size(file) >= configLogger.fileSizeLimit())
    {
        std::cout << '\n' << "identifyFile (file_size)" << '\n';
        std::cout << std::filesystem::file_size(file) << "\n";
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