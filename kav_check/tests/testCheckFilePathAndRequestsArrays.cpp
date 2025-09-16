//
// Created by Alexander on 27.03.2025.
//

#include "gtest/gtest.h"

#include "testGeneral.h"



//Проверить массив на заполненность
TEST(TestCheckArray, arrayFilled)
{
    putFiles();

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkArray(testConstants::configTemplate["files"])};

    bool result{};

    if (errorCode == kav::ErrorCode::no_error)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}

//Проверить массив на пустоту
TEST(TestCheckArray, arrayNotFilled)
{
    putFiles();

    kav::ErrorCode errorCode{kav::OperationFileAndJSON::checkArray(testConstants::configWrongTemplate["files"])};

    bool result{};

    if (errorCode == kav::ErrorCode::error_array_empty)
    {
        result = true;
    }

    ASSERT_TRUE(result);
}



//Для примера, когда можно контролировать правильность составления теста
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