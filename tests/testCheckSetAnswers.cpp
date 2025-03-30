//
// Created by Alexander on 28.03.2025.
//



#include <iostream>
#include "gtest/gtest.h"

#include "converterJSON.h"
#include "general.h"
#include "testGeneral.h"



TEST(TestCheckConverterJSON, setAnswersJSON)
{
    //Создать объект с фиктивными параметрами. Объект используется только для проверки соответствия записи в JSON-объект результатов поиска
    ConverterJSON test{constants::configTemplate, constants::requestsTemplate};

    test.setAnswersJSON(testConstants::answers, test.getMaxResponses());

    bool result{test.getAnswersJSON() == testConstants::answersTest};

    ASSERT_TRUE(result);
}