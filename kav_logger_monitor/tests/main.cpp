//
// Created by Alexander on 30.03.2025.
//



#include "gtest/gtest.h"



#include "testGeneral.h"





int main()
{
    //https://stackoverflow.com/questions/52539568/how-i-can-read-simply-console-output

    //Запустить все тесты
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}