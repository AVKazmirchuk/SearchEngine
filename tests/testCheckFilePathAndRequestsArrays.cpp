//
// Created by Alexander on 27.03.2025.
//

#include "gtest/gtest.h"

#include "checkFileException.h"
#include "converterJSON.h"
#include "general.h"
#include "testGeneral.h"



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
                                                    ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY)};

    ASSERT_TRUE(result);
}

//Проверить массив путей файлов документов на отсутствие некоторых файлов (смотреть вывод в консоль)
TEST(TestCheckFilePathsArray, filePathsArrayWrongFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(testConstants::configWrongArray, constants::requestsTemplate,
                                                    ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY)};

    ASSERT_TRUE(result);
}

//Проверить массив путей файлов документов на пустоту
TEST(TestCheckFilePathsArray, filePathsArrayNotFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(testConstants::configWrongTemplate, constants::requestsTemplate,
                                                    ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY)};

    ASSERT_FALSE(result);
}

//Проверить массив запросов на заполненность
TEST(TestCheckFilePathsArray, requestsArrayFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(constants::configTemplate, constants::requestsTemplate,
                                                    ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY)};

    ASSERT_TRUE(result);
}

//Проверить массив запросов на пустоту
TEST(TestCheckFilePathsArray, requestsArrayNotFilled)
{
    bool result{testCheckFilePathsAndRequestsArrays(constants::configTemplate, testConstants::requestsWrongTemplate,
                                                    ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY)};

    ASSERT_FALSE(result);
}