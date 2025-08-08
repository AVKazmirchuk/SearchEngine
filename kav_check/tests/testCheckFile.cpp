#include <filesystem>

#include "gtest/gtest.h"

#include "kav/operationFileAndJSON.h"
#include "testGeneral.h"



//Запустить проверку файла на существование, на неповреждённость JSON-структуры, на соответствие JSON-структуры шаблону
bool testCheckFile(const std::string& filePath, const kav::JSON& templateJSON, kav::ErrorCode errorCode)
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
}

//Запустить проверку файла на существование
TEST(TestCheckFile, fileExist)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_file_missing)};

    deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку файла на несуществование
TEST(TestCheckFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_file_missing)};

    deleteFiles();

    ASSERT_FALSE(result);
}

//Запустить проверку файла на неповреждённость JSON-структуры
TEST(TestCheckFile, fileJSONStructureValid)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_json_structure_corrupted)};

    deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку файла на повреждённость JSON-структуры
TEST(TestCheckFile, fileJSONStructureNotValid)
{
    putFiles();

    const std::string configNotValidFilePath{"configNotValid.json"};

    bool result{testCheckFile(configNotValidFilePath, constants::configTemplate, ErrorCode::error_json_structure_corrupted)};

    deleteFiles();

    ASSERT_FALSE(result);
}
//Запустить проверку файла на соответствие JSON-структуры шаблону
TEST(TestCheckFile, fileJSONStructureMatch)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::error_json_structure_not_match)};

    deleteFiles();

    ASSERT_TRUE(result);
}

//Запустить проверку файла на несоответствие JSON-структуры шаблону
TEST(TestCheckFile, fileJSONStructureNotMatch)
{
    putFiles();

    const std::string configNotMatchFilePath{"configNotMatch.json"};

    bool result{testCheckFile(configNotMatchFilePath, constants::configTemplate, ErrorCode::error_json_structure_not_match)};

    deleteFiles();

    ASSERT_FALSE(result);
}
