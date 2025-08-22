#include <filesystem>

#include "windows.h"

#include "gtest/gtest.h"

//#include "kav/operationFileAndJSON.h"
#include "testGeneral.h"



//Запустить проверку файла на существование, на неповреждённость JSON-структуры, на соответствие JSON-структуры шаблону
/*bool testCheckFile(const std::string& filePath, const kav::JSON& templateJSON, kav::ErrorCode errorCode)
{
    try 
    {
        //Запустить проверку файла
        kav::checkFile(filePath, templateJSON);
        //Файл соответствует всем требованиям
        return true;
    }
    //Одно из требований не выполняется
    catch (const kav::CheckFileException& e)
    {
        //Если коды исключения не совпадают - тест составлен неверно
        EXPECT_EQ(e.getErrorCode(), errorCode);
        //Файл не соответствует какому-либо требованию
        return false;
    }
}*/

//Запустить проверку файла на существование, на неповреждённость JSON-структуры, на соответствие JSON-структуры шаблону
/*bool testCheckFile(const std::string& filePath, const kav::JSON& templateJSON, kav::ErrorCode errorCode)
{


    try
    {
        //Запустить проверку файла
        kav::checkFile(filePath, templateJSON);
        //Файл соответствует всем требованиям
        return true;
    }
    //Одно из требований не выполняется
    catch (const kav::CheckFileException& e)
    {
        //Если коды исключения не совпадают - тест составлен неверно
        EXPECT_EQ(e.getErrorCode(), errorCode);
        //Файл не соответствует какому-либо требованию
        return false;
    }
}*/

//Запустить проверку на запись JSON-файла (файл присутствует, не блокируется)
TEST(TestWriteJSONFile, fileExist)
{
    putFiles();

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile(constants::configFilePath, testConstants::configTemplate)};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    //deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку на запись JSON-файла (файл отсутствует или присутствует, не блокируется)
/*TEST(TestWriteJSONFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile(constants::configFilePath, testConstants::configTemplate)};

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_missing)
    {
        result = true;
    }

    //deleteFiles();

    ASSERT_TRUE(result);
}*/

//Запустить проверку на запись JSON-файла (файл блокируется)
TEST(TestWriteJSONFile, fileNotOpen)
{
    putFiles();

    //Создать объект для записи
    HANDLE hFile=CreateFile(constants::configFilePath.c_str(), // file to open
                            GENERIC_READ, // open for
                            0x00000000, // share for
                            NULL, // default security
                            OPEN_ALWAYS, // OPEN_EXISTING // existing file only
                            FILE_ATTRIBUTE_NORMAL, // normal file
                            NULL // no attr. template
    );

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile(constants::configFilePath, testConstants::configTemplate)};

    CloseHandle(hFile);

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_not_open_write)
    {
        result = true;
    }

    //deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку на запись JSON-файла (файл не записывается)
TEST(TestWriteJSONFile, fileNotWrite)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    system("connectDisk.bat");

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile("w://config.json", testConstants::configTemplate)};

    if (errorCode == kav::ErrorCode::error_file_not_write) std::cout << "error_file_not_write";

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_not_write)
    {
        result = true;
    }

    //deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл присутствует, открыт для чтения)
TEST(TestReadJSONFile, fileExist)
{
    putFiles();

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configFilePath)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    //deleteFiles();

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

    //deleteFiles();

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

    //deleteFiles();

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

    //deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (повреждённая JSON-структура)
TEST(TestReadJSONFile, fileJSONStructureNotValid)
{
    putFiles();

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configNotValid)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::error_json_structure_corrupted)
    {
        result = true;
    }

    //deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение текстового файла (файл присутствует, открыт для чтения)
TEST(TestReadTextFile, fileExist)
{
    putFiles();

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readTextFile(constants::fileText)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    //deleteFiles();

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

    //deleteFiles();

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

    //deleteFiles();

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

    //deleteFiles();

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

    //deleteFiles();

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

    //deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку файла на существование
/*TEST(TestCheckFile, fileExist)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_file_missing)};

    deleteFiles();

    ASSERT_TRUE(result);
}*/

//Запустить проверку файла на несуществование
/*TEST(TestCheckFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_file_missing)};

    deleteFiles();

    ASSERT_FALSE(result);
}*/

//Запустить проверку файла на неповреждённость JSON-структуры
/*TEST(TestCheckFile, fileJSONStructureValid)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_json_structure_corrupted)};

    deleteFiles();

    ASSERT_TRUE(result);
}*/

//Запустить проверку файла на повреждённость JSON-структуры
/*TEST(TestCheckFile, fileJSONStructureNotValid)
{
    putFiles();

    const std::string configNotValidFilePath{"configNotValid.json"};

    bool result{testCheckFile(configNotValidFilePath, constants::configTemplate, ErrorCode::error_json_structure_corrupted)};

    deleteFiles();

    ASSERT_FALSE(result);
}*/
//Запустить проверку файла на соответствие JSON-структуры шаблону
/*TEST(TestCheckFile, fileJSONStructureMatch)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_json_structure_not_match)};

    deleteFiles();

    ASSERT_TRUE(result);
}*/

//Запустить проверку файла на несоответствие JSON-структуры шаблону
/*TEST(TestCheckFile, fileJSONStructureNotMatch)
{
    putFiles();

    const std::string configNotMatchFilePath{"configNotMatch.json"};

    bool result{testCheckFile(configNotMatchFilePath, constants::configTemplate, ErrorCode::error_json_structure_not_match)};

    deleteFiles();

    ASSERT_FALSE(result);
}*/
