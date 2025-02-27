//
// Created by Alexander on 19.02.2025.
//

#ifndef SEARCH_ENGINE_PARALLELIZATION_H
#define SEARCH_ENGINE_PARALLELIZATION_H



#include <list>
#include <thread>

#include "invertedIndex.h"


class Parallelization
{

public:

    Parallelization() = default;

    //void startThreads(void (InvertedIndex::*definitionWord)(), const std::vector<std::string> &container);


private:

    //Контейнер потоков
    std::list<std::thread> threads;
};



#endif //SEARCH_ENGINE_PARALLELIZATION_H
