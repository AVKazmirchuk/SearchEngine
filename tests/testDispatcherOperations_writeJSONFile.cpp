//
// Created by AKazmirchuk on 12.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции writeJSONFile
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

    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
    DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), timePoint, errorLevel);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Возвратить соответствие фактического уровня логирования ожидаемому
    return isMatchingErrorLevel(timePoint, strErrorLevel);
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
TEST(TestDispatcherOperations_writeJSONFile, fatal)
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

    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Обнулить результат операции
    bool result{};

    try
    {
        //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
        DispatcherOperations::writeJSONFile(ProgramArguments::jsonFileName(), Bases::jsonTest(), ProgramArguments::formatByWidth(), timePoint, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Возвратить соответствие фактического уровеня логирования ожидаемому
    result = result && isMatchingErrorLevel(timePoint, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//Тестирование функции writeJSONFile