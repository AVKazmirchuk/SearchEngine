//
// Created by AKazmirchuk on 12.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



std::filesystem::path getFilePath()
{
    std::filesystem::path file;

    for (const auto& filePath : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
         file = filePath;
    }

    return file;
}



TEST(TestDispatcherOperations_writeJSONFile, general)
{




}

TEST(TestDispatcherOperations_writeJSONFile, message)
{

}

TEST(TestDispatcherOperations_writeJSONFile, errorLevel)
{
    std::filesystem::remove_all(ProgramArguments::logsFolderName());

    std::filesystem::create_directory(ProgramArguments::logsFolderName());
    std::cout << "qaz";
    //Создать объект для записи. Запретить доступ к файлу
    HANDLE hFile=CreateFile(ProgramArguments::jsonFileName().c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            nullptr, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            nullptr // no attr. template
    );
std::cout << "qaz";
    DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), ProgramArguments::messageTest(), ErrorLevel::error);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    std::cout << "qaz";

    std::string log{kav::OperationFileAndJSON::readTextFile(getFilePath().filename()).first};

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