//
// Created by Alexander on 08.05.2025.
//



#include <thread>

#include "kav/logger.h"
#include "kav/operationFileAndJSON.h"
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
        //Момент времени последнего изменения текущего файла
        std::chrono::system_clock::time_point tpCurrent{};

        //Прочитать последнюю строку лог-файла
        auto tmp = OperationFileAndJSON::readLastLineFromTextFile(entry.path().string());

        //Если при чтении ошибок не было
        if (tmp.second == ErrorCode::no_error)
        {
            //Получить момент времени из строки
            tpCurrent = getTimePointFromString(tmp.first);
        }
        else
        {
            //Обработать ошибку чтения лог-файла. В этой функции избыточно
            handleErrorReadingLogFile(entry.path());
        }

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
