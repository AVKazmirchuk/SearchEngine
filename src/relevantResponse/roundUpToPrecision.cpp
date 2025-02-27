//
// Created by Alexander on 24.02.2025.
//



#include <cmath>

#include "relevantResponse.h"



namespace constants
{
    extern int precision;
}



float RelevantResponse::roundUpToPrecision(float value)
{
    //Вычислить порядок числа в соответствии с точностью
    int numberOrder{static_cast<int>(std::pow(10, constants::precision))};
    //Округлить значение в соответствии с точностью
    return std::round(value*numberOrder)/numberOrder;
}
