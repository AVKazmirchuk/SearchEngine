//
// Created by Alexander on 28.03.2025.
//



#include <iostream>
#include "gtest/gtest.h"

#include "converterJSON.h"
#include "general.h"
#include "testGeneral.h"



//Проверить запись в JSON-объект результатов поиска
TEST(TestCheckConverterJSON, setAnswersJSON)
{
    int precision{6};

    //Создать объект с фиктивными параметрами. Объект используется только для проверки соответствия записи в JSON-объект результатов поиска
    ConverterJSON converterJsonObj{testConstants::configTemplate, testConstants::requestsTemplate, precision};

    converterJsonObj.setAnswersJSON(testConstants::answers, converterJsonObj.getMaxResponses());

    bool result{converterJsonObj.getAnswersJSON() == testConstants::answersTest};

    ASSERT_TRUE(result);
}