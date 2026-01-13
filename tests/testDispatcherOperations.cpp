//
// Created by AKazmirchuk on 12.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



std::string getLastFilePath()
{
    std::filesystem::directory_entry directoryEntry;
    std::chrono::system_clock::time_point timePoint{};

    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        std::chrono::system_clock::time_point currentTimePoint{std::chrono::clock_cast<std::chrono::system_clock>(currentDirectoryEntry.last_write_time())};
        if (currentTimePoint > timePoint)
        {
            directoryEntry = currentDirectoryEntry;
        }
    }

    return directoryEntry.path().string();
}

/*std::string timePointToString(const std::chrono::system_clock::time_point& timePoint)
{
    //Преобразовать момент времени в объект времени POSIX
    std::time_t t{std::chrono::system_clock::to_time_t(timePoint)};

    //Задать размер строки
    std::string ts(256,0);

    //Преобразовать время в строку, и задать размер строки
    ts.resize(std::strftime(&ts[0], ts.size(), configLogger.dateTimeFormat().c_str(), std::localtime(&t)));

    //Вернуть строку времени
    return ts;
}*/


TEST(TestDispatcherOperations_writeJSONFile, general)
{




}

TEST(TestDispatcherOperations_writeJSONFile, message)
{

}

TEST(TestDispatcherOperations_writeJSONFile, errorLevel)
{
    //std::filesystem::remove_all(ProgramArguments::logsFolderName());

    //std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Создать объект для записи. Запретить доступ к файлу
    HANDLE hFile=CreateFile(ProgramArguments::jsonFileName().c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            nullptr, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            nullptr // no attr. template
    );

    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};
    std::cout << now;

    std::chrono::duration<int64_t, std::ratio<1, 1000000000>> timeSinceEpoch{now.time_since_epoch()};
    std::cout << timeSinceEpoch;
    timeSinceEpoch.count();

        //std::time_t now_c = std::chrono::system_clock::to_time_t(timePoint);
        //std::cout << "Текущее системное время: " << std::ctime(&now_c) << std::endl;


    DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), ProgramArguments::dispatcherOperations_writeJSONFile_info(), ErrorLevel::info);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    std::string fileName{getLastFilePath()};

    std::cout << "fileName: " << fileName << '\n';

    std::string log{kav::OperationFileAndJSON::readTextFile(fileName).first};

    std::cout << log << '\n';

    //Обнулить результат операции
    bool result{};

    if (log.find_last_of(ProgramArguments::dispatcherOperations_writeJSONFile_info()) != std::string::npos &&
        log.find_last_of(ProgramArguments::errorLevel_info()) != std::string::npos)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

TEST(TestDispatcherOperations_writeJSONFile, callingFunction)
{

}