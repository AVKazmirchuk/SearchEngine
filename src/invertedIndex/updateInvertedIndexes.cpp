//
// Created by Alexander on 27.01.2025.
//



#include "invertedIndex.h"



void InvertedIndex::updateInvertedIndexes()
{
    //Очистить базу инвертированных индексов
    clearInvertedIndexes();

    //Запустить инвертированную индексацию документов в отдельных потоках
    startInvertedIndexing();

    //Сортировать базу инвертированного индекса по возрастанию ID документа
    //sortByAscendingDocumentID();
}
