//
// Created by Alexander on 16.03.2025.
//



#include "gtest/gtest.h"

#include "invertedIndex.h"

#include "testGeneral.h"



//Запустить проверку на создание объекта, обновление базы инвертированных индексов,
// получение ссылки на базу инвертированных индексов
TEST(TestUpdateInvertedIndexes, updateInvertedIndexes)
{
    //Создать объект документов
    InvertedIndex invertedIndex(Bases::documents());

    //Обновить базу документов или путей файлов документов
    invertedIndex.updateInvertedIndexes();

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (invertedIndex.getInvertedIndexes() == Bases::invertedIndex());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, обновление базы инвертированных индексов,
// получение ссылки на базу инвертированных индексов, действительное фактическое количество потоков
TEST(TestUpdateInvertedIndexes, desiredNumberOfThreads_3)
{
    //Создать объект документов
    InvertedIndex invertedIndex(Bases::documents(), ProgramArguments::maximumAllowableErrorsNumber_0(), ProgramArguments::desiredNumberOfThreads_3());

    //Обновить базу документов или путей файлов документов
    invertedIndex.updateInvertedIndexes();

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (invertedIndex.getNumberOfThreads() == ProgramArguments::desiredNumberOfThreads_3());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, обновление базы инвертированных индексов,
// получение ссылки на базу инвертированных индексов, действительное максимальное количество непрочитанных файлов и
// признак формирования базы документов или путей файлов документов
TEST(TestUpdateInvertedIndexes, maximumAllowableErrorsNumber_1)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    //DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект документов
    InvertedIndex invertedIndex(Bases::paths_file003_missing(),
                                ProgramArguments::maximumAllowableErrorsNumber_1(),
                                ProgramArguments::desiredNumberOfThreads(),
                                ProgramArguments::documentsBaseOrPathsBase_no());

    //Обновить базу документов или путей файлов документов
    invertedIndex.updateInvertedIndexes();

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (invertedIndex.getDocumentsBaseOrPathsBase() == ProgramArguments::documentsBaseOrPathsBase_no() &&
            invertedIndex.getMaximumAllowableErrorsNumber() == ProgramArguments::maximumAllowableErrorsNumber_1() &&
            invertedIndex.getInvertedIndexes() == Bases::invertedIndex_file003_missing());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, обновление базы инвертированных индексов,
// получение ссылки на базу инвертированных индексов, и признак формирования базы документов или путей файлов документов
TEST(TestUpdateInvertedIndexes, documentsBaseOrPathsBase_no)
{
    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    //DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    //Создать объект документов
    InvertedIndex invertedIndex(Bases::paths(),
                                ProgramArguments::maximumAllowableErrorsNumber_0(),
                                ProgramArguments::desiredNumberOfThreads(),
                                ProgramArguments::documentsBaseOrPathsBase_no());

    //Обновить базу документов или путей файлов документов
    invertedIndex.updateInvertedIndexes();

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (invertedIndex.getInvertedIndexes() == Bases::invertedIndex());

    //Проверить утверждение
    ASSERT_TRUE(result);
}


/**
 * Тесты из руководства по проекту
 */

//Получить список структур инвертированного индекса соответствующего слова
std::vector<Entry> getInvertedIndexStructures(const std::map<std::string, std::vector<Entry>>& invertedIndexes, const std::string& request)
{
    //Слово в базе инвертированных индексов существует
    if (invertedIndexes.find(request) != invertedIndexes.end())
    {
        //Возвратить список структур инвертированного индекса
        return invertedIndexes.find(request)->second;
    }
    else
        //Слово в базе инвертированных индексов не существует
    {
        //Возвратить пустой список структур инвертированного индекса
        return std::vector<Entry>{};
    }
}

//Запустить проверку обновления базы инвертированных индексов
void TestInvertedIndexFunctionality(
        const std::vector<std::string>& docs,
        const std::vector<std::string>& requests,
        const std::vector<std::vector<Entry>>& expected
) {
    std::vector<std::vector<Entry>> result;
    InvertedIndex idx(docs);
    idx.updateInvertedIndexes();
    for(auto& request : requests) {
        std::vector<Entry> word_count = getInvertedIndexStructures(idx.getInvertedIndexes(), request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}

//Проверить обновление базы инвертированных индексов. Тест №1. Просто тест
TEST(TestCaseInvertedIndex, TestBasic) {
const std::vector<std::string> docs = {
        "london is the capital of great britain",
        "big ben is the nickname for the Great bell of the striking clock"
};
const std::vector<std::string> requests = {"london", "the"};
const std::vector<std::vector<Entry>> expected = {
        {
                {0, 1}
        },
        {
                {0, 1}, {1, 3}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}

//Проверить обновление базы инвертированных индексов. Тест №2. Один из запросов найден только в одном документе
TEST(TestCaseInvertedIndex, TestBasic2) {
const std::vector<std::string> docs = {
        "milk milk milk milk water water water",
        "milk water water",
        "milk milk milk milk milk water water water water water",
        "americano cappuccino"
};
const std::vector<std::string> requests = {"milk", "water", "cappuccino"};
const std::vector<std::vector<Entry>> expected = {
        {
                {0, 4}, {1, 1}, {2, 5}
        },
        {
                {0, 3}, {1, 2}, {2, 5}
        },
        {
                {3, 1}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}

//Проверить обновление базы инвертированных индексов. Тест №3. Один из запросов не найден ни в одном документе
TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
const std::vector<std::string> docs = {
        "a b c d e f g h i j k l",
        "statement"
};
const std::vector<std::string> requests = {"m", "statement"};
const std::vector<std::vector<Entry>> expected = {
        {
        },
        {
                {1, 1}
        }
};
TestInvertedIndexFunctionality(docs, requests, expected);
}

