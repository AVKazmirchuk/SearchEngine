//
// Created by Alexander on 27.01.2025.
//



#include "invertedIndex.h"



void InvertedIndex::updateInvertedIndexes(const unsigned int desiredNumberOfThreads, const unsigned int maximumAllowableErrorsNumber)
{
    //Очистить базу инвертированных индексов
    clearInvertedIndexes();

    //Запустить инвертированную индексацию документов в отдельных потоках
    startInvertedIndexing(desiredNumberOfThreads, maximumAllowableErrorsNumber);

    //Сортировать базу инвертированного индекса по возрастанию ID документа
    //sortByAscendingDocumentID();
}
