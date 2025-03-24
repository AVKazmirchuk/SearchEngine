//
// Created by Alexander on 24.03.2025.
//



#include <iostream>
#include <limits>

#include "logger.h"



void pressAnyKey(const char* message)
{
    Logger().info("***   " + std::string(message) + "   ***");

    // reset any error flags
    std::cin.clear();
    // ignore any characters in the input buffer until we find a newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // get one more char from the user (waits for user to press enter)
    std::cin.get();
}

void pressAnyKey()
{
    //Logger().info("***   " + std::string(message) + "   ***");

    // reset any error flags
    std::cin.clear();
    // ignore any characters in the input buffer until we find a newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // get one more char from the user (waits for user to press enter)
    std::cin.get();
}