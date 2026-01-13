//
// Created by AKazmirchuk on 12.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



/**
  * Преобразовать момент времени одного типа в другой
  * @tparam TP Тип момента времени
  * @param tp Момент времени преобразующегося типа
  * @return Момент времени проеобразованного типа
  */
template<typename TP>
std::time_t to_time_t(TP tp)
{
    auto sctp = time_point_cast<std::chrono::system_clock::duration>(tp - TP::clock::now() + std::chrono::system_clock::now());
    return std::chrono::system_clock::to_time_t(sctp);
}

std::string getLastFilePath()
{
    std::filesystem::directory_entry directoryEntry;
    std::chrono::system_clock::time_point timePoint{};

    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        std::chrono::system_clock::time_point currentTimePoint{std::chrono::clock_cast<std::chrono::system_clock>(currentDirectoryEntry.last_write_time())};
        //std::time_t currentTime_t{std::chrono::system_clock::to_time_t(currentDirectoryEntry.last_write_time())};
        if (currentTimePoint > timePoint)
         {
             directoryEntry = currentDirectoryEntry;
         }
        std::cout << currentDirectoryEntry.path().filename().string();
    }
std::cout << directoryEntry.path().filename().string();
    return directoryEntry.path().filename().string();
}



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
    std::cout << "qaz1";
    //Создать объект для записи. Запретить доступ к файлу
    HANDLE hFile=CreateFile(ProgramArguments::jsonFileName().c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            nullptr, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            nullptr // no attr. template
    );
std::cout << "qaz2";
    DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), ProgramArguments::messageTest(), ErrorLevel::info);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    std::string fileName{getLastFilePath()};

    std::cout << "qaz3: " << fileName;

    std::string log{kav::OperationFileAndJSON::readTextFile(fileName).first};

std::cout << "log: " << log;

    //Обнулить результат операции
    bool result{};

    if (log.find(ProgramArguments::errorLevel_info()) != std::string::npos)
    {
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

TEST(TestDispatcherOperations_writeJSONFile, callingFunction)
{

}