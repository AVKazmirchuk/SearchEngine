//
// Created by Alexander on 01.02.2025.
//

#ifndef SEARCH_ENGINE_RELATIVEINDEX_H
#define SEARCH_ENGINE_RELATIVEINDEX_H



#include <utility>



/**
 * Структура относительного индекса
 */
struct RelativeIndex
{
    /**
     * ID документа
     */
    std::size_t docID;

    /**
     * Относительная релевантность ответа
     */
    float rank;

    operator std::pair<int, float>() const
    {
        return {static_cast<int>(docID), rank};
    }

    bool operator ==(const RelativeIndex& other) const {
        return (docID == other.docID && rank == other.rank);
    }
};



#endif //SEARCH_ENGINE_RELATIVEINDEX_H
