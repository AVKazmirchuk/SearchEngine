//
// Created by Alexander on 22.02.2025.
//



#include "invertedIndex.h"



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