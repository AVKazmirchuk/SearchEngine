//
// Created by AKazmirchuk on 12.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Получить путь текущего файла логирования
std::string getLastFilePath()
{
    //Подготовить переменные
    std::filesystem::directory_entry directoryEntry;
    std::chrono::system_clock::time_point timePoint{};

    //Для каждого файла директории
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        //Преобразовать время в нужный тип
        std::chrono::system_clock::time_point currentTimePoint{std::chrono::clock_cast<std::chrono::system_clock>(currentDirectoryEntry.last_write_time())};
        //Если время изменения текущего файла позже
        if (currentTimePoint > timePoint)
        {
            //Запомнить файл
            directoryEntry = currentDirectoryEntry;
        }
    }

    //Вернуть путь файла
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

//Проверить функцию на уровень логирования
bool testWriteJSONFile(ErrorLevel errorLevel, const std::string& strErrorLevel)
{
    //Создать объект для записи. Запретить доступ к файлу
    HANDLE hFile=CreateFile(ProgramArguments::jsonFileName().c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            nullptr, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            nullptr // no attr. template
    );

    //Получить текущий момент времени
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};

    //Отметка времени
    std::string timePoint{timePointToString(now)};

    //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
    DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), timePoint, errorLevel);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Получить путь текущего лог-файла
    std::string fileName{getLastFilePath()};

    //Прочитать лог-файл
    std::string log{kav::OperationFileAndJSON::readTextFile(fileName).first};

    //Обнулить результат операции
    bool result{};

    //Определить позицию отметки времени в лог-файле
    std::string::size_type found{log.rfind(timePoint)};

    //Если отметка присутствует
    if (found != std::string::npos)
    {
        //Определить начало строки с отметкой в лог-файле
        std::string::size_type begin{log.rfind('\n', found)};
        //Определить конец строки с отметкой в лог-файле
        std::string::size_type end{log.find('\n',found)};

        //Выделить строку сообщения с отметкой
        std::string logLine{log.substr(begin + 1, end - begin - 1)};

        //Если уровень логирования совпадает
        if (logLine.find(strErrorLevel) != std::string::npos)
        {
            //Установить результат операции
            result = true;
        }
    }

    //Возвратить результат операции
    return result;
}

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_writeJSONFile, debug)
{
    //Обнулить результат операции
    bool result{};

    result = testWriteJSONFile(ErrorLevel::debug, ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestDispatcherOperations_writeJSONFile, info)
{
    //Обнулить результат операции
    bool result{};

    result = testWriteJSONFile(ErrorLevel::info, ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestDispatcherOperations_writeJSONFile, wrning)
{
    //Обнулить результат операции
    bool result{};

    result = testWriteJSONFile(ErrorLevel::warning, ProgramArguments::errorLevel_warn());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestDispatcherOperations_writeJSONFile, error)
{
    //Обнулить результат операции
    bool result{};

    result = testWriteJSONFile(ErrorLevel::error, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
/*TEST(TestDispatcherOperations_writeJSONFile, fatal)
{
    //Обнулить результат операции
    bool result{};

    result = testWriteJSONFile(ErrorLevel::fatal, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}*/