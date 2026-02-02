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

    //Вычислить интервал времени, в течение которого можно хранить файл
    std::chrono::duration<double, std::ratio<1>> storageTimeLimit = Weeks(configLogger.weeksStorage()) + Days(configLogger.daysStorage()) + Hours(configLogger.hoursStorage()) +
                                                                    Minutes(configLogger.minutesStorage()) + Seconds(configLogger.secondsStorage());

    //Для каждого файла в директории
    for (auto& entry : std::filesystem::directory_iterator(directoryPath))
    {
        std::ifstream inFile(entry.path(), std::ios::binary);

        char ch2;

        inFile.seekg(-1, std::ios::end);
        for (int i{1}; i <= 10; ++i)
        {
            inFile.get(ch2);
            std::cout << ch2;
            inFile.seekg(-2, std::ios::cur);
        }


        inFile.seekg(-2, std::ios::end);
        std::istream::pos_type pos;
        for (unsigned long charNumber{1}; charNumber <= 2; ++charNumber)
        {
            char ch;

            while (inFile.get(ch))
            {
                std::cout << ch;
                if (ch == '\n')
                {

                    if (charNumber == 2)
                    {
                        pos = inFile.tellg();
                        break;
                    }
                    break;
                }
                inFile.seekg(-2, std::ios::cur);
            }
        }

        //Объявить переменные
        std::string dateFirstEntry, timeFirstEntry;
        //Прочитать дату и время первой записи в файле
        inFile >> dateFirstEntry >> timeFirstEntry;

        //Закрыть файл
        inFile.close();
        std::cout << '\n' << "deleteFilesByRetentionPeriod" << '\n';
        std::cout << "dateFirstEntry: " << dateFirstEntry << ", " << "timeFirstEntry: " << timeFirstEntry << '\n';

        //Преобразовать строки даты и времени, прочитанных из файла, в удобный формат времени для дальнейшего использования
        std::tm tm{};
        std::istringstream iss{dateFirstEntry + ' ' + timeFirstEntry};
        iss >> std::get_time(&tm, configLogger.dateTimeFormat().c_str());
        std::time_t tt{std::mktime(&tm)};
        std::chrono::system_clock::time_point tpCurrent{std::chrono::system_clock::from_time_t(tt)};

        //Определить подстроку с наносекундами
        std::string strNanoseconds{timeFirstEntry.substr(timeFirstEntry.find('.') + 1)};

        //Получить из подстроки наносекунды
        std::chrono::nanoseconds nanoseconds{std::stoull(strNanoseconds)};

        //Получить момент времени с наносекундами
        tpCurrent += nanoseconds;



        //Определить момент времени последнего изменения файла
        //auto lastWriteTime = std::filesystem::last_write_time(entry.path());

        //Преобразовать момент времени последнего изменения файла в нужный тип
        //std::time_t ttCurrent = to_time_t(lastWriteTime);
        //std::chrono::system_clock::time_point tpCurrent{std::chrono::system_clock::from_time_t(ttCurrent)};

        //Определить текущий интервал хранения файла
        std::chrono::system_clock::duration storageTimeCurrent = std::chrono::system_clock::now() - tpCurrent;

        //Текущий интервал хранения файла больше либо равно предельного
        if (storageTimeCurrent >= storageTimeLimit)
        {
            //Удалить текущий файл из директории
            std::filesystem::remove(entry.path());
        }
        else
        {
            //Добавить в контейнер пару пути и момента времени последнего изменения файла
            logs.emplace_back(entry.path(), tpCurrent);
        }
    }

    std::cout << '\n' << "deleteFilesByRetentionPeriod" << '\n';
    for (auto& elem : logs)
    {
        std::cout << "path: " << elem.first << ", " << "time: " << elem.second << '\n';
    }
}

void kav::Logger::setup()
{
    //Удалить файлы по сроку хранения
    deleteFilesByRetentionPeriod(configLogger.filesDirectory());

    //Определить файл для записи
    identifyFile(configLogger.filesDirectory());

    //std::cout << "\nInSetup, size: " << std::filesystem::file_size(file) << "\n";
}
