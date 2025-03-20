//
// Created by Alexander on 09.03.2025.
//



#include <iostream>



#include "logger.h"



void Logger::error(const std::string& message)
{
    std::cout << '\n' << "error: " << message << '\n';
}