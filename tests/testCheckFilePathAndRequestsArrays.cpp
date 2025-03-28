//
// Created by Alexander on 27.03.2025.
//

#include "gtest/gtest.h"

#include "checkFileException.h"
#include "converterJSON.h"
#include "general.h"
#include "testGeneral.h"



bool testCheckFilePathsAndRequestsArrays(const JSON& configJSON, const JSON& requestsJSON, ErrorCode errorCode)
{
    try
    {
        ConverterJSON tmp(configJSON, requestsJSON);
        return true;
    }
    catch (const CheckFileException& e)
    {
        EXPECT_EQ(e.getErrorCode(), errorCode);
        return false;
    }
}

TEST(TestCheckFilePathsArray, filePathsArrayFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(constants::configTemplate, constants::requestsTemplate,
                                                    ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY)};

    ASSERT_TRUE(result);
}

TEST(TestCheckFilePathsArray, filePathsArrayWrongFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(testConstants::configWrongArray, constants::requestsTemplate,
                                                    ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY)};

    ASSERT_TRUE(result);
}

TEST(TestCheckFilePathsArray, filePathsArrayNotFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(testConstants::configWrongTemplate, constants::requestsTemplate,
                                                    ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY)};

    ASSERT_FALSE(result);
}

TEST(TestCheckFilePathsArray, requestsArrayFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(constants::configTemplate, constants::requestsTemplate,
                                                    ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY)};

    ASSERT_TRUE(result);
}

TEST(TestCheckFilePathsArray, requestsArrayNotFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(constants::configTemplate, testConstants::requestsWrongTemplate,
                                                    ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY)};

    ASSERT_FALSE(result);
}