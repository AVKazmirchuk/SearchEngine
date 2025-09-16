#include <filesystem>

#include "windows.h"

#include "gtest/gtest.h"

#include "testGeneral.h"



//Запустить проверку на запись JSON-файла (файл присутствует или отсутствует, открыт, записывается)
TEST(TestWriteJSONFile, fileExist)
{
    //Записать файлы для тестирования
    putFiles();

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile(constants::configFilePath, testConstants::configTemplate)};

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
    HANDLE hFile=CreateFile(constants::configFilePath.c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            NULL, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING - existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            NULL // no attr. template
    );

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile("config/config.json", testConstants::configTemplate)};

    //Закрыть дескриптор. Освободить файл
    CloseHandle(hFile);

    //Обнулить результат операции
    bool result{};

    //Если открыть файл не удалось
    if (errorCode == kav::ErrorCode::error_file_not_open_write)
    {
        //Установить результат операции
        result = true;
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на запись JSON-файла (файл не записывается)
TEST(TestWriteJSONFile, fileNotWrite)
{
    //Записать файлы для тестирования
    putFiles();

    //Удалить проверяемый файл
    std::filesystem::remove(constants::configFilePath);

    //Подключить диск с проверяемым файлом
    system("connectDisk.bat");

    //Записать JSON-файл
    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile("w://config.json", testConstants::configTemplate)};

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
}

//Запустить проверку на чтение JSON-файла (файл присутствует, открыт, читается, JSON-структура неповреждена)
TEST(TestReadJSONFile, fileExist)
{
    putFiles();

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configFilePath)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл отсутствует)
TEST(TestReadJSONFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configFilePath)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_missing)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл не открыт)
TEST(TestReadJSONFile, fileNotOpen)
{
    putFiles();

    //Создать объект для записи
    HANDLE hFile=CreateFile(constants::configFilePath.c_str(), // file to open
                     GENERIC_WRITE, // open for writing
                     FILE_SHARE_WRITE, // share for writing
                     NULL, // default security
                     OPEN_ALWAYS, // OPEN_EXISTING // existing file only
                     FILE_ATTRIBUTE_NORMAL, // normal file
                     NULL // no attr. template
                     );

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configFilePath)).second};

    CloseHandle(hFile);

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_not_open_read)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл не читается)
TEST(TestReadJSONFile, fileNotRead)
{
    putFiles();

    system("connectDisk.bat");

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile("w://config.json")).second};

    if (errorCode == kav::ErrorCode::error_file_not_read) std::cout << "error_file_not_read";


    bool result{};

    if (errorCode == kav::ErrorCode::error_file_not_read)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (JSON-структура повреждена)
TEST(TestReadJSONFile, fileJSONStructureNotValid)
{
    putFiles();

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configNotValid)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::error_json_structure_corrupted)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл присутствует, открыт, читается)
TEST(TestReadTextFile, fileExist)
{
    putFiles();

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile(constants::fileText)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл отсутствует)
TEST(TestReadTextFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::fileText);

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile(constants::fileText)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_missing)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл не открыт)
TEST(TestReadTextFile, fileNotOpen)
{
    putFiles();

    //Создать объект для записи
    HANDLE hFile=CreateFile(constants::fileText.c_str(), // file to open
                            GENERIC_WRITE, // open for writing
                            FILE_SHARE_WRITE, // share for writing
                            NULL, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING // existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            NULL // no attr. template
    );

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile(constants::fileText)).second};

    CloseHandle(hFile);

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_not_open_read)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл не читается)
TEST(TestReadTextFile, fileNotRead)
{
    putFiles();

    system("connectDisk.bat");

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile("w://file001.txt")).second};

    if (errorCode == kav::ErrorCode::error_file_not_read) std::cout << "error_file_not_read";

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_not_read)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку JSON-структуры на соответствие шаблону (файл соответствует)
TEST(TestCheckJSONStructureMatch, JSONStructureMatch)
{
    putFiles();

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkJSONStructureMatch(constants::configFilePath, testConstants::configTemplate, testConstants::configTemplate)};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Запустить проверку JSON-структуры на соответствие шаблону (файл не соответствует)
TEST(TestCheckJSONStructureMatch, JSONStructureNotMatch)
{
    putFiles();

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkJSONStructureMatch(constants::configFilePath, testConstants::configNotMatchTemplate, testConstants::configTemplate)};

    bool result{};

    if (errorCode == kav::ErrorCode::error_json_structure_not_match)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}
