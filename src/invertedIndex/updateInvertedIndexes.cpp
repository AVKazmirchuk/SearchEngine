//
// Created by Alexander on 27.01.2025.
//



#include "invertedIndex.h"



void InvertedIndex::updateInvertedIndexes(const unsigned int desiredNumberOfThreads)
{
    //Очистить базу инвертированных индексов
    clearInvertedIndexes();

    if (!documents.empty())
    {
        //Запустить инвертированную индексацию документов в отдельных потоках
        startInvertedIndexing(documents, desiredNumberOfThreads);
    }
    else
    {
        //Запустить инвертированную индексацию документов в отдельных потоках для используемой базы путей файлов документов
        startInvertedIndexing(documentsPaths, desiredNumberOfThreads);
    }

    //Сортировать базу инвертированного индекса по возрастанию ID документа
    //sortByAscendingDocumentID();
}
