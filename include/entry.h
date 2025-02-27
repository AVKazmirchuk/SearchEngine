//
// Created by Alexander on 15.02.2025.
//

#ifndef SEARCH_ENGINE_ENTRY_H
#define SEARCH_ENGINE_ENTRY_H



#include <cstddef>



/**
 * Структура инвертированного индекса
 */
struct Entry
{
    /**
     * ID документа
     */
    std::size_t docID;

    /**
     * Число вхождений слова в документе
     */
    std::size_t count;

// Данный оператор необходим для проведения тестовых сценариев
    bool operator ==(const Entry& other) const
    {
        return (docID == other.docID && count == other.count);
    }
};



#endif //SEARCH_ENGINE_ENTRY_H
