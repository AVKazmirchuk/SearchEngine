//
// Created by Alexander on 19.02.2025.
//

#include <string>
#include <vector>

#include "parallelization.h"


/*
//Вспомогательная функция запуска потоков для функций
void Parallelization::startThreads(void (InvertedIndex::*definitionWord)(),
                                   const std::vector<std::string> &container)
{
    //Запуск потоков
    for (const auto &elem: container) {
        threads.emplace_back(definitionWord, this, elem);
    }

    //Ожидание окончания работы потоков
    for (auto &&thread: threads)
        thread.join();

    threads.clear();
}
*/