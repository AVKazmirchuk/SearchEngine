//
// Created by Alexander on 01.04.2025.
//



#include <iostream>

#include "logger.h"



void Logger::info(const std::string& message)
{
    std::cout << '\n' << message << '\n';
}

void Logger::warn(const std::string& message)
{
    std::cout << '\n' << "warning: " << message << '\n';
}

void Logger::error(const std::string& message)
{
    std::cout << '\n' << "error: " << message << '\n';
}

void Logger::fatal(const std::string& message)
{
    std::cout << '\n' << "fatal: " << message << '\n';
}