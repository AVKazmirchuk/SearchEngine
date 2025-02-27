//
// Created by Alexander on 22.02.2025.
//



#include <algorithm>

#include "invertedIndex.h"



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
