//
// Created by AKazmirchuk on 22.10.2025.
//

#ifndef SEARCH_ENGINE_SOLUTION_TIMER_H
#define SEARCH_ENGINE_SOLUTION_TIMER_H



#include <chrono>



class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> begin{Clock::now()};

public:
    void reset()
    {
        begin = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - begin).count();
    }
};



#endif //SEARCH_ENGINE_SOLUTION_TIMER_H
