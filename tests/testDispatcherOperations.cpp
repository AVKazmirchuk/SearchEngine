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

//Перевести отметку времени в строку
std::string timePointToString(const std::chrono::system_clock::time_point& now)
{
    //Преобразовать момент времени в объект времени POSIX
    std::time_t t{std::chrono::system_clock::to_time_t(now)};

    //Задать размер строки
    std::string ts(256,0);

    //Преобразовать время в строку, и задать размер строки
    ts.resize(std::strftime(&ts[0], ts.size(), "%Y-%m-%d %H:%M:%S.", std::localtime(&t)));

    //Преобразовать момент времени в секунды
    std::chrono::system_clock::time_point nowSeconds{std::chrono::time_point_cast<std::chrono::seconds>(now)};

    //Получить наносекунды
    std::chrono::nanoseconds nanoseconds{now - nowSeconds};

    //Преобразовать наносекунды в строку
    std::stringstream ss4;
    ss4 << nanoseconds.count();
    std::string strNanosecondsCount;
    ss4 >> strNanosecondsCount;

    //Вернуть строку времени
    return ts + strNanosecondsCount;
}

void runWriteJSONFile(std::string& timePoint)
{
    //Записать JSON-файл
    DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), timePoint, ErrorLevel::info);
}



TEST(TestDispatcherOperations_writeJSONFile, errorLevel)
{
    //std::filesystem::remove_all(ProgramArguments::logsFolderName());

    //std::filesystem::create_directory(ProgramArguments::logsFolderName());

    //Создать объект для записи. Запретить доступ к файлу
    HANDLE hFile=CreateFile(ProgramArguments::jsonFileName().c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            NULL, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            nullptr // no attr. template
    );

    //Получить текущий момент времени
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};

    //Перевести отметку времени в строку
    std::string timePoint{timePointToString(now)};

    //Записать JSON-файл
    //DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), timePoint, ErrorLevel::info);
    runWriteJSONFile(timePoint);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    std::string fileName{getLastFilePath()};

    std::cout << "fileName: " << fileName << '\n';

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string log{kav::OperationFileAndJSON::readTextFile(fileName).first};

    std::cout << log << log.size() << ' ' << timePoint;

    //Обнулить результат операции
    bool result{};

    std::string::size_type found{log.rfind(timePoint)};
    std::string::size_type begin{log.rfind('\n', found)};
    std::string::size_type end{log.find('\n',found)};

    std::cout << '\n' << found;
    std::cout << '\n' << begin;
    std::cout << '\n' << end;

    if (found != std::string::npos)
    {
        std::cout << '\n' << log.substr(begin + 1, end - begin - 1) << '\n';
        std::string logLine{log.substr(begin + 1, end - begin - 1)};

        if (logLine.find(ProgramArguments::errorLevel_info()) != std::string::npos)
        {
            result = true;
        }
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

