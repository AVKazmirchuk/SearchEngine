#include <filesystem>

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

//Запустить проверку на запись JSON-файла (файл отсутствует)
//kav::ErrorCode kav::OperationFileAndJSON::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth, const boost::source_location &callingFunction)
/*TEST(TestCheckFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::writeJSONFile(constants::configFilePath, testConstants::configTemplate)};

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_missing)
    {
        result = false;
    }
    else
    {
        result = true;
    }

    deleteFiles();

    ASSERT_FALSE(result);
}*/

//Запустить проверку на чтение JSON-файла (файл присутствует, открыт для чтения)
TEST(TestCheckFile, fileExist)
{
    putFiles();

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configFilePath)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    deleteFiles();

    ASSERT_TRUE(result);
}
//Запустить проверку на чтение JSON-файла (файл отсутствует)
TEST(TestCheckFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configFilePath)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_missing)
    {
        result = true;
    }

    deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку на чтение JSON-файла (файл не открыт для чтения)
TEST(TestCheckFile, fileNotOpen)
{
    //putFiles();

    //Создать объект для записи
    //std::ofstream outFile(constants::configFilePath, std::ios::app);

    kav::ErrorCode errorCode{(kav::OperationFileAndJSON::readJSONFile(constants::configFilePath)).second};

    bool result{};

    if (errorCode == kav::ErrorCode::error_file_not_open_read)
    {
        result = true;
    }

    deleteFiles();

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
