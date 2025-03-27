#include <filesystem>

#include "gtest/gtest.h"

#include "checkFileException.h"
#include "general.h"



void putFiles()
{
    std::filesystem::remove("config.json");
    std::filesystem::remove("configNotValid.json");
    std::filesystem::remove("configNotMatch.json");
    std::filesystem::copy("../../tests/resources/config.json", "config.json");
    std::filesystem::copy("../../tests/resources/configNotValid.json", "configNotValid.json");
    std::filesystem::copy("../../tests/resources/configNotMatch.json", "configNotMatch.json");
}

void deleteFiles()
{
    std::filesystem::remove("configNotValid.json");
    std::filesystem::remove("configNotMatch.json");
}

bool testCheckFile(const std::string& filePath, const JSON& templateJSON, ErrorCode errorCode)
{
    try 
    {
    checkFile(filePath, templateJSON);
    return true;
    }
    catch (const CheckFileException& e)
    {
        EXPECT_EQ(e.getErrorCode(), errorCode);
        return false;
    }
}

TEST(TestCheckFile, fileExist)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_MISSING)};

    deleteFiles();

    ASSERT_TRUE(result);
}

TEST(TestCheckFile, fileNotExist)
{
    putFiles();

    std::filesystem::remove(constants::configFilePath);

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_MISSING)};

    deleteFiles();

    ASSERT_FALSE(result);
}

TEST(TestCheckFile, fileJSONStructureValid)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED)};

    deleteFiles();

    ASSERT_TRUE(result);
}

TEST(TestCheckFile, fileJSONStructureNotValid)
{
    putFiles();

    const std::string configNotValidFilePath{"configNotValid.json"};

    bool result{testCheckFile(configNotValidFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED)};

    deleteFiles();

    ASSERT_FALSE(result);
}

TEST(TestCheckFile, fileJSONStructureMatch)
{
    putFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH)};

    deleteFiles();

    ASSERT_TRUE(result);
}

TEST(TestCheckFile, fileJSONStructureNotMatch)
{
    putFiles();

    const std::string configNotMatchFilePath{"configNotMatch.json"};

    bool result{testCheckFile(configNotMatchFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH)};

    deleteFiles();

    ASSERT_FALSE(result);
}
