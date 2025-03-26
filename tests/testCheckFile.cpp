#include "gtest/gtest.h"

#include "checkFile.h"
#include "checkFileException.h"
#include "general.h"



void testCheckFile(const std::string& filePath, const JSON& template, ErrorCode errorCode)
{
    try 
    {
    checkFile(filePath, template);
    FAIL();
    }
    catch (std::exception& e)
    {
      ASSERT_STREQ(e.getErrorCode(), errorCode);
    }
}

TEST(TestCheckFile, configExist)
{
  std::string wrongFilePath{wrongConfig.json};  

  testCheckFile(wrongConfig.json, constants::configTemplate, ERROR_FILE_MISSING);
}

TEST(TestCheckFile, configJSONStructureValid)
{
  testCheckFile(constants::configFilePath, constants::configTemplate, ERROR_FILE_STRUCTURE_CORRUPTED);
}

TEST(TestCheckFile, configJSONStructureMatch)
{
  testCheckFile(constants::configFilePath, constants::configTemplate, ERROR_FILE_STRUCTURE_NOT_MATCH);
}
