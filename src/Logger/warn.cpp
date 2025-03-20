//
// Created by Alexander on 09.03.2025.
//



#include <iostream>



#include "logger.h"



void Logger::warn(const std::string& message)
{
    std::cout << '\n' << "warn: " << message << '\n';
}