//
// Created by Alexander on 22.02.2025.
//



#include "invertedIndex.h"
#include "kav/logger.h"



void InvertedIndex::addWord(const std::string& word, std::size_t docID)
{
    //Установить защиту на поиск и добавление слова в базе инвертированных индексов
    std::unique_lock<std::mutex> lgAddWord(mutexFindAddWord);

    //Найти слово в базе инвертированных индексов
    auto positionWord{invertedIndexes.find(word)};

    //Слово в базе инвертированных индексов не существует
    if (positionWord == invertedIndexes.end())
    {
        //Добавить слово со структурой инвертированного индекса в базу инвертированных индексов
        invertedIndexes.emplace(word, std::vector<Entry>{{docID, 1}});
    }
    else
        //Слово в базе инвертированных индексов существует
    {
        //Снять защиту на поиск и добавление слова в базе инвертированных индексов
        lgAddWord.unlock();
        //Установить защиту на поиск и добавление структуры инвертированного индекса
        std::unique_lock<std::mutex> lgAddEntry(mutexFindAddEntry);

        //Найти структуру инвертированного индекса с равным ID документа нового и существующего слов
        auto positionDocId{std::find_if(positionWord->second.begin(), positionWord->second.end(),
                                        [docID = docID](const Entry& entry)
                                        {
                                            return entry.docID == docID;
                                        })};
        //ID документа нового и существующего слов равно
        if (positionDocId != positionWord->second.end())
        {
            //Увеличить количество вхождений слова в документе
            ++positionDocId->count;
        }
        else
            //ID документа нового и существующего слов не равно
        {
            //Добавить структуру инвертированного индекса для нового ID документа по слову
            invertedIndexes[word].push_back({docID, 1});
        }
    }
}

void InvertedIndex::defineWord(std::size_t docID, const std::string& document)
{
    //Разделители слов
    const std::string  delims(" ");
    //Начальный и конечный (за последним символом) индексы слова
    std::string::size_type begIdx, endIdx;

    //Искать начало первого слова
    begIdx = document.find_first_not_of(delims);

    //Искать начало первого слова
    while (begIdx != std::string::npos)
    {
        //Искать конец текущего слова
        endIdx = document.find_first_of(delims, begIdx);

        //Конец слова равен концу строки
        if (endIdx == std::string::npos)
        {
            //Конец слова - это конец строки
            endIdx = document.length();
        }

        //Добавить слово и структуру инвертированного индекса в базу инвертированных индексов
        addWord(std::string(document, begIdx, endIdx - begIdx), docID);

        //Искать начало следующего слова
        begIdx = document.find_first_not_of(delims, endIdx);
    }
}

void InvertedIndex::startInvertedIndexing()
{
    //Контейнер результатов потоков
    std::list<std::future<void>> futures;

    //Запустить потоки
    for (std::size_t docID{}; docID < documents.size(); ++docID)
    {
        //Запустить поток для определения слова (выделения) в документе
        futures.push_back(std::async(&InvertedIndex::defineWord, this, docID, std::cref(documents[docID])));
    }

    try
    {
        //Ожидать завершения потоков
        for (auto &future: futures)
            future.wait();
    }
    //Обработать все исключения, выброшенные в потоках
    catch (const std::exception& e)
    {
        throw;
    }
}