#include <filesystem>

#include "gtest/gtest.h"

#include "checkFile.h"
#include "checkFileException.h"
#include "general.h"



void preparedFiles()
{
    std::filesystem::remove("config.json");
    std::filesystem::remove("requests.json");
    std::filesystem::copy("../../tests/resources/config.json", "config.json");
    std::filesystem::copy("../../tests/resources/requests.json", "requests.json");
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
    preparedFiles();

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_MISSING)};

    ASSERT_TRUE(result);

    //std::cout << "The file exists: " << filePath;
}

TEST(TestCheckFile, fileNotExist)
{
    preparedFiles();

    std::filesystem::remove(constants::configFilePath);

    bool result{testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_MISSING)};

    ASSERT_FALSE(result);

    //std::cout << "The file does not exist: " << filePath;
}

TEST(TestCheckFile, configJSONStructureValid)
{
  testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED);
}

TEST(TestCheckFile, configJSONStructureMatch)
{
  testCheckFile(constants::configFilePath, constants::configTemplate, ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH);
}
