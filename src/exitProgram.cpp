//
// Created by Alexander on 20.02.2025.
//



#include <iostream>



void exitProgram(const char* error)
{
    std::cout << "\n\n" << "EXCEPTION: " << error << "\n\n" << std::endl;
    std::exit(EXIT_FAILURE);
}