//
// Created by Alexander on 08.01.2026.
//



#include "gtest/gtest.h"

#include "documents.h"

#include "testGeneral.h"



//Запустить проверку на создание объекта, обновление базы документов или путей файлов документов по const l-ref,
// и получение ссылки на базу документов или путей файлов документов
TEST(TestUpdateDocuments, byConstLRef)
{
    //Создать объект документов
    Documents documents;

    //Обновить базу документов или путей файлов документов
    documents.updateDocuments(Bases::documents());

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (documents.getDocuments() == Bases::documents());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, обновление базы документов или путей файлов документов по r-ref,
// и получение ссылки на базу документов или путей файлов документов
TEST(TestUpdateDocuments, byRRef)
{
    //Создать объект документов
    Documents documents;

    //Установить временной переменной базу документов
    std::vector<std::string> tmpDocuments{Bases::documents()};

    //Обновить базу документов или путей файлов документов
    documents.updateDocuments(std::move(tmpDocuments));

    //Обнулить результат операции
    bool result{};

    //Установить результат операции
    result = (documents.getDocuments() == Bases::documents());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Запустить проверку на создание объекта, обновление базы документов или путей файлов документов по const l-ref,
// очистку базы документов или путей файлов документов, получение ссылки на базу документов или путей файлов документов
TEST(TestClearDocuments, clearDocuments)
{
    //Создать объект документов
    Documents documents;

    //Обновить базу документов или путей файлов документов
    documents.updateDocuments(Bases::documents());

    //Обнулить результат операции
    bool result{};

    //Очистить базу документов или путей файлов документов
    documents.clearDocuments();

    //Установить результат операции
    result = documents.getDocuments().empty();

    //Проверить утверждение
    ASSERT_TRUE(result);
}