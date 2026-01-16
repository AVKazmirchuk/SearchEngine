//
// Created by Alexander on 16.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции readJSONFile
//Проверить функцию на уровень логирования
bool testReadJSONFile(ErrorLevel errorLevel, const std::string& strErrorLevel)
{
    //Создать объект для записи. Запретить доступ для чтения
    HANDLE hFile=CreateFile(ProgramArguments::readJSONFile().c_str(), // file to open
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
    DispatcherOperations::readJSONFile(ProgramArguments::readJSONFile(), timePoint, errorLevel);

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Возвратить соответствие фактического уровня логирования ожидаемому
    return isMatchingErrorLevel(timePoint, strErrorLevel);
}

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_readJSONFile, debug)
{
    //Обнулить результат операции
    bool result{};

    result = testReadJSONFile(ErrorLevel::debug, ProgramArguments::errorLevel_debug());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования info
TEST(TestDispatcherOperations_readJSONFile, info)
{
    //Обнулить результат операции
    bool result{};

    result = testReadJSONFile(ErrorLevel::info, ProgramArguments::errorLevel_info());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования warning
TEST(TestDispatcherOperations_readJSONFile, wrning)
{
    //Обнулить результат операции
    bool result{};

    result = testReadJSONFile(ErrorLevel::warning, ProgramArguments::errorLevel_warn());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования error
TEST(TestDispatcherOperations_readJSONFile, error)
{
    //Обнулить результат операции
    bool result{};

    result = testReadJSONFile(ErrorLevel::error, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования fatal
TEST(TestDispatcherOperations_readJSONFile, fatal)
{
    //Создать объект для записи. Запретить доступ для чтения
    HANDLE hFile=CreateFile(ProgramArguments::readJSONFile().c_str(), // file to open
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
        DispatcherOperations::readJSONFile(ProgramArguments::readJSONFile(), timePoint, ErrorLevel::fatal);
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
}//Тестирование функции readJSONFile