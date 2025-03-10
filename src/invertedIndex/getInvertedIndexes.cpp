//
// Created by Alexander on 15.02.2025.
//



#include "invertedIndex.h"



const std::map<std::string, std::vector<Entry>>& InvertedIndex::getInvertedIndexes()
{
    //Вернуть ссылку на базу инвертированных индексов
    return invertedIndexes;
}
