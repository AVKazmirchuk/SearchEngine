//
// Created by Alexander on 23.03.2025.
//



#include "gtest/gtest.h"

#include "converterJSON.h"
#include "relevantResponse.h"
#include "invertedIndex.h"
#include "testGeneral.h"


//Проверить рассчёт релевантности ответов. Тест №1. Просто тест
TEST(TestCaseRelevantResponse, TestSimple) {
    const std::vector<std::string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const std::vector<std::string> request = {"milk water", "sugar"};
    const int precision{6};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3},
                    {3, 0.0}
            },
            {
                    {0, 0.0},
                    {1, 0.0},
                    {2, 0.0},
                    {3, 0.0}
            }
    };
    InvertedIndex idx(docs);
    idx.updateInvertedIndexes();
    RelevantResponse srv(idx.getInvertedIndexes(), request, precision);
    srv.updateRelevantResponses();
    std::vector<std::vector<RelativeIndex>> result = srv.getRelevantResponses();
    ASSERT_EQ(result, expected);
}

//Проверить рассчёт релевантности ответов. Тест №2. Ограничение количества ответов
TEST(TestCaseRelevantResponse, TestTopMaxResponses) {
    const std::vector<std::string> docs = {
            "london is the capital of great britain",
            "paris is the capital of france",
            "berlin is the capital of germany",
            "rome is the capital of italy",
            "madrid is the capital of spain",
            "lisboa is the capital of portugal",
            "bern is the capital of switzerland",
            "moscow is the capital of russia",
            "kiev is the capital of ukraine",
            "minsk is the capital of belarus",
            "astana is the capital of kazakhstan",
            "beijing is the capital of china",
            "tokyo is the capital of japan",
            "bangkok is the capital of thailand",
            "welcome to moscow the capital of russia the third rome",
            "amsterdam is the capital of netherlands",
            "helsinki is the capital of finland",
            "oslo is the capital of norway",
            "stockholm is the capital of sweden",
            "riga is the capital of latvia",
            "tallinn is the capital of estonia",
            "warsaw is the capital of poland",
    };
    const std::vector<std::string> request = {"moscow is the capital of russia"};
    const int precision{6};
    const int maxResponses{5};
    const std::vector<std::vector<RelativeIndex>> expected = {
            {
                    {7, 1},
                    {14, 1},
                    {0, 0.666667},
                    {1, 0.666667},
                    {2, 0.666667}
            }
    };
    InvertedIndex idx(docs);
    idx.updateInvertedIndexes();
    RelevantResponse srv(idx.getInvertedIndexes(), request, precision);
    srv.updateRelevantResponses();
    std::vector<std::vector<RelativeIndex>> result = srv.getRelevantResponses();
    result[0].resize(maxResponses);

    ASSERT_EQ(result, expected);
}

