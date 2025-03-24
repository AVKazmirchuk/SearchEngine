//
// Created by Alexander on 22.02.2025.
//



#include "invertedIndex.h"



void InvertedIndex::startInvertedIndexing()
{
    //Контейнер результатов потоков
    std::list<std::future<void>> asyncs;

    //Запустить потоки
    for (std::size_t docID{}; docID < documents.size(); ++docID)
    {
        //Запустить поток для определения слова (выделения) в документе
        asyncs.emplace_back(std::async(&InvertedIndex::defineWord, this, docID, documents[docID]));
    }

    try
    {
        //Ожидать завершения потоков
        for (auto &future: asyncs)
            future.wait();
    }
        //Обработать все исключения, выброшенные в потоках
    catch (const std::exception& e)
    {
        Logger().fatal("EXCEPTION: " + std::string(e.what()));
        exitProgram();
    }
}