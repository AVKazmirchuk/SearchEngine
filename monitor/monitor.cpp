//
// Created by Alexander on 20.04.2025.
//



#include <iostream>
#include <string>
#include <sstream>

#include "termcolor.h"



std::string determineLevel(const std::string& message)
{
    std::stringstream ss(message);
    std::string level;

    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');

    return level;
}

void outputToConsole(const std::string& message)
{
    //Определить уровень логирования
    std::string level{determineLevel(message)};

    //Вывести сообщение на монитор в своём цвете в соответствии уровню логирования
    if (level == "DEBUG:") std::cout << termcolor::grey << message << std::endl;
    else if (level == "INFO:") std::cout << termcolor::white << message << std::endl;
    else if (level == "WARNING:") std::cout << termcolor::yellow << message << std::endl;
    else if (level == "ERROR:") std::cout << termcolor::magenta << message << std::endl;
    else if (level == "FATAL:") std::cout << termcolor::red << message << std::endl;
}