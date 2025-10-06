#include <filesystem>

#include "windows.h"

#include "gtest/gtest.h"

#include "testGeneral.h"



/*
 * Для прохождения тестов на запись-чтение файлов (в процессе) для эмуляции ошибки используется сетевой диск. При записи-чтении
 * диск отключается. Перед запуском тестов надо расшарить директорию с правами на запись, положить файлы config.json, file001.txt, и поправить файлы: connect.bat,
 * disconnect.bat. Раскомментировать эти функции проверки. Также в файле operationFileAndJSON.cpp надо раскомментировать строки
 * с командой system(...). Есть вариант использовать для этого Windows API, но там всё не так просто. Другого автоматического
 * способа не нашёл для эмуляции ошибки. Пока хоть что-то. Поэтому эти функции проверки закомментированы.
 */

//Запустить проверку на запись JSON-файла (файл присутствует или отсутствует, открыт, записывается)
TEST(TestWriteTextFile, fileExist)
{
    //Записать файлы для тестирования
    putFiles();

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeTextFile(testConstants::textFileForWrite, testConstants::textString)};

    //Обнулить результат операции
    bool result{};

    //Если запись файла прошла без ошибок
    if (errorCode == kav::ErrorCode::no_error)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на запись JSON-файла (файл не открыт)
TEST(TestWriteTextFile, fileNotOpen)
{
    //Записать файлы для тестирования
    putFiles();

    //Создать объект для записи. Запретить доступ к файлу
    HANDLE hFile=CreateFile(testConstants::textFileForWrite.c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            NULL, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            NULL // no attr. template
    );

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeTextFile(testConstants::textFileForWrite, testConstants::textString)};

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Обнулить результат операции
    bool result{};

    //Если открыть файл на запись не удалось
    if (errorCode == kav::ErrorCode::error_file_not_open_write)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на запись JSON-файла (файл не записывается)
/*TEST(TestWriteTextFile, fileNotWrite)
{
    //Записать файлы для тестирования
    putFiles();

    //Удалить проверяемый файл
    std::filesystem::remove(testConstants::textFileForWrite);

    //Подключить диск с проверяемым файлом
    system("connectDisk.bat");

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeTextFile("w:\\" + testConstants::textFileForWrite, testConstants::textString)};

    //Обнулить результат операции
    bool result{};

    //Если записать файл не удалось
    if (errorCode == kav::ErrorCode::error_file_not_write)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}*/

//Запустить проверку на запись JSON-файла (файл присутствует или отсутствует, открыт, записывается)
TEST(TestWriteJSONFile, fileExist)
{
    //Записать файлы для тестирования
    putFiles();

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile(testConstants::configFilePath, testConstants::configTemplate)};

    //Обнулить результат операции
    bool result{};

    //Если запись файла прошла без ошибок
    if (errorCode == kav::ErrorCode::no_error)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на запись JSON-файла (файл не открыт)
TEST(TestWriteJSONFile, fileNotOpen)
{
    //Записать файлы для тестирования
    putFiles();

    //Создать объект для записи. Запретить доступ к файлу
    HANDLE hFile=CreateFile(testConstants::configFilePath.c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            NULL, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            NULL // no attr. template
    );

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile(testConstants::configFilePath, testConstants::configTemplate)};

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Обнулить результат операции
    bool result{};

    //Если открыть файл на запись не удалось
    if (errorCode == kav::ErrorCode::error_file_not_open_write)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на запись JSON-файла (файл не записывается)
/*TEST(TestWriteJSONFile, fileNotWrite)
{
    //Записать файлы для тестирования
    putFiles();

    //Удалить проверяемый файл
    std::filesystem::remove(testConstants::configFilePath);

    //Подключить диск с проверяемым файлом
    system("connectDisk.bat");

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile("w:\\" + testConstants::configFilePath, testConstants::configTemplate)};

    //Обнулить результат операции
    bool result{};

    //Если записать файл не удалось
    if (errorCode == kav::ErrorCode::error_file_not_write)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}*/

//Запустить проверку на чтение JSON-файла (файл присутствует, открыт, читается, JSON-структура неповреждена)
TEST(TestReadJSONFile, fileExist)
{
    //Записать файлы для тестирования
    putFiles();

    //Прочитать JSON-файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(testConstants::configFilePath)).second};

    //Обнулить результат операции
    bool result{};

    //Если чтение файла прошло без ошибок
    if (errorCode == kav::ErrorCode::no_error)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл отсутствует)
TEST(TestReadJSONFile, fileNotExist)
{
    //Записать файлы для тестирования
    putFiles();

    //Удалить проверяемый файл
    std::filesystem::remove(testConstants::configFilePath);

    //Прочитать JSON-файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(testConstants::configFilePath)).second};

    //Обнулить результат операции
    bool result{};

    //Если файл отсутствует
    if (errorCode == kav::ErrorCode::error_file_missing)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл не открыт)
TEST(TestReadJSONFile, fileNotOpen)
{
    //Записать файлы для тестирования
    putFiles();

    //Создать объект для записи. Запретить доступ для чтения
    HANDLE hFile=CreateFile(testConstants::configFilePath.c_str(), // file to open
                     GENERIC_WRITE, // open for writing
                     FILE_SHARE_WRITE, // share for writing
                     NULL, // default security
                     OPEN_ALWAYS, // OPEN_EXISTING // existing file only
                     FILE_ATTRIBUTE_NORMAL, // normal file
                     NULL // no attr. template
                     );

    //Прочитать JSON-файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(testConstants::configFilePath)).second};

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Обнулить результат операции
    bool result{};

    //Если открыть файл на чтение не удалось
    if (errorCode == kav::ErrorCode::error_file_not_open_read)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл не читается)
/*TEST(TestReadJSONFile, fileNotRead)
{
    //Записать файлы для тестирования
    putFiles();

    //Подключить диск с проверяемым файлом
    system("connectDisk.bat");

    //Прочитать JSON-файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile("w:\\" + testConstants::configFilePath)).second};

    //Обнулить результат операции
    bool result{};

    //Если файл не читается
    if (errorCode == kav::ErrorCode::error_file_not_read)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}*/

//Запустить проверку на чтение JSON-файла (JSON-структура повреждена)
TEST(TestReadJSONFile, fileJSONStructureNotValid)
{
    //Записать файлы для тестирования
    putFiles();

    //Прочитать JSON-файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(testConstants::configNotValid)).second};

    //Обнулить результат операции
    bool result{};

    //Если JSON-структура повреждена
    if (errorCode == kav::ErrorCode::error_json_structure_corrupted)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл присутствует, открыт, читается)
TEST(TestReadTextFile, fileExist)
{
    //Записать файлы для тестирования
    putFiles();

    //Прочитать файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile(testConstants::textFile)).second};

    //Обнулить результат операции
    bool result{};

    //Если чтение файла прошло без ошибок
    if (errorCode == kav::ErrorCode::no_error)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл отсутствует)
TEST(TestReadTextFile, fileNotExist)
{
    //Записать файлы для тестирования
    putFiles();

    //Удалить проверяемый файл
    std::filesystem::remove(testConstants::textFile);

    //Прочитать файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile(testConstants::textFile)).second};

    //Обнулить результат операции
    bool result{};

    //Если файл отсутствует
    if (errorCode == kav::ErrorCode::error_file_missing)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл не открыт)
TEST(TestReadTextFile, fileNotOpen)
{
    //Записать файлы для тестирования
    putFiles();

    //Создать объект для записи. Запретить чтение
    HANDLE hFile=CreateFile(testConstants::textFile.c_str(), // file to open
                            GENERIC_WRITE, // open for writing
                            FILE_SHARE_WRITE, // share for writing
                            NULL, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING // existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            NULL // no attr. template
    );

    //Прочитать файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile(testConstants::textFile)).second};

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Обнулить результат операции
    bool result{};

    //Если открыть файл на чтение не удалось
    if (errorCode == kav::ErrorCode::error_file_not_open_read)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл не читается)
/*TEST(TestReadTextFile, fileNotRead)
{
    //Записать файлы для тестирования
    putFiles();

    //Подключить диск с проверяемым файлом
    system("connectDisk.bat");

    //Прочитать файл
    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile("w:\\" + testConstants::textFile)).second};

    //Обнулить результат операции
    bool result{};

    //Если файл не читается
    if (errorCode == kav::ErrorCode::error_file_not_read)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}*/

//Запустить проверку JSON-структуры на соответствие шаблону (файл соответствует)
TEST(TestCheckJSONStructureMatch, JSONStructureMatch)
{
    //Записать файлы для тестирования
    putFiles();

    //Проверить JSON-структуру на соответствие шаблону
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkJSONStructureMatch(testConstants::configTemplate, testConstants::configTemplate)};

    //Обнулить результат операции
    bool result{};

    //Если JSON-структура соответствует шаблону
    if (errorCode == kav::ErrorCode::no_error)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку JSON-структуры на соответствие шаблону (файл не соответствует)
TEST(TestCheckJSONStructureMatch, JSONStructureNotMatch)
{
    //Записать файлы для тестирования
    putFiles();

    //Проверить JSON-структуру на соответствие шаблону
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkJSONStructureMatch(testConstants::configNotMatchTemplate, testConstants::configTemplate)};

    //Обнулить результат операции
    bool result{};

    //Если JSON-структура не соответствует шаблону
    if (errorCode == kav::ErrorCode::error_json_structure_not_match)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить массив на заполненность
TEST(TestCheckArray, arrayFilled)
{
    //Записать файлы для тестирования
    putFiles();

    //Проверить массив JSON-объекта на пустоту
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkArray(testConstants::configTemplate[testConstants::files])};

    //Обнулить результат операции
    bool result{};

    //Если проверка прошла без ошибок
    if (errorCode == kav::ErrorCode::no_error)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить массив на пустоту
TEST(TestCheckArray, arrayNotFilled)
{
    //Записать файлы для тестирования
    putFiles();

    //Проверить массив JSON-объекта на пустоту
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkArray(testConstants::configArrayEmptyTemplate[testConstants::files])};

    //Обнулить результат операции
    bool result{};

    //Если массив пустой
    if (errorCode == kav::ErrorCode::error_array_empty)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}



//Для примера, когда можно контролировать правильность составления теста. Не работающие тесты!
/*
//Проверить пути файлов документов, запросы (соответствующие массивы в объектах)
bool testCheckFilePathsAndRequestsArrays(const JSON& configJSON, const JSON& requestsJSON, ErrorCode errorCode)
{
    try
    {
        //Создать объект (косвенно проверить требования запустив проверку)
        ConverterJSON converterJsonObj(configJSON, requestsJSON);
        //Объект соответствует всем требованиям
        return true;
    }
    //Одно из требований не выполняется
    catch (const CheckFileException& e)
    {
        //Если коды исключения не совпадают - тест составлен неверно
        EXPECT_EQ(e.getErrorCode(), errorCode);
        //Объект не соответствует какому-либо требованию
        return false;
    }
}

//Проверить массив путей файлов документов на заполненность
TEST(TestCheckFilePathsArray, filePathsArrayFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(constants::configTemplate, constants::requestsTemplate,
                                                    ErrorCode::error_file_paths_array_empty)};

    ASSERT_TRUE(result);
}

//Проверить массив путей файлов документов на отсутствие некоторых файлов (смотреть вывод в консоль)
TEST(TestCheckFilePathsArray, filePathsArrayWrongFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(testConstants::configWrongArray, constants::requestsTemplate,
                                                    ErrorCode::error_file_paths_array_empty)};

    ASSERT_TRUE(result);
}

//Проверить массив путей файлов документов на пустоту
TEST(TestCheckFilePathsArray, filePathsArrayNotFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(testConstants::configWrongTemplate, constants::requestsTemplate,
                                                    ErrorCode::error_file_paths_array_empty)};

    ASSERT_FALSE(result);
}*/