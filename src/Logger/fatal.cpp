//
// Created by Alexander on 09.03.2025.
//



#include "logger.h"



void Logger::fatal(const std::string& message)
{
    std::cout << '\n' << "fatal: " << message << '\n';
}