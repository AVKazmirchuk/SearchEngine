//
// Created by Alexander on 16.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции readTextFile
//Проверить функцию на уровень логирования
bool testReadTextFile(ErrorLevel errorLevel, const std::string& strErrorLevel)
{
    //Создать объект для записи. Запретить чтение
    HANDLE hFile=CreateFile(ProgramArguments::readTextFile().c_str(), // file to open
                            GENERIC_WRITE, // open for writing
                            FILE_SHARE_WRITE, // share for writing
                            nullptr, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING // existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            nullptr // no attr. template
    );

    //Отметка времени
    std::string timePoint{getTimePoint()};

    //Записать JSON-файл, указав отметку времени (будет использоваться для поиска строки в лог-файле)
    DispatcherOperations::readTextFile(ProgramArguments::readTextFile(), timePoint, errorLevel);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Возвратить соответствие фактического уровня логирования ожидаемому
    return isMatchingErrorLevel(timePoint, strErrorLevel);
}

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_readTextFile, debug)
{
    //Обнулить результат операции
    bool result{};

    result = testReadTextFile(ErrorLevel::debug, ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestDispatcherOperations_readTextFile, info)
{
    //Обнулить результат операции
    bool result{};

    result = testReadTextFile(ErrorLevel::info, ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestDispatcherOperations_readTextFile, wrning)
{
    //Обнулить результат операции
    bool result{};

    result = testReadTextFile(ErrorLevel::warning, ProgramArguments::errorLevel_warn());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestDispatcherOperations_readTextFile, error)
{
    //Обнулить результат операции
    bool result{};

    result = testReadTextFile(ErrorLevel::error, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
TEST(TestDispatcherOperations_readTextFile, fatal)
{
    //Создать объект для записи. Запретить доступ для чтения
    HANDLE hFile=CreateFile(ProgramArguments::readTextFile().c_str(), // file to open
                            GENERIC_WRITE, // open for writing
                            FILE_SHARE_WRITE, // share for writing
                            nullptr, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING // existing file only
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
        DispatcherOperations::readTextFile(ProgramArguments::readTextFile(), timePoint, ErrorLevel::fatal);
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
}//Тестирование функции readTextFile