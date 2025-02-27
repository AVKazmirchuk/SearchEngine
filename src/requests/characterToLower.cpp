//
// Created by Alexander on 15.02.2025.
//



#include <string>

#include "requests.h"



//Преобразование всех символов в нижний регистр
std::string& Requests::characterToLower(std::string& line)
{
    for (auto& elem : line)
    {
        elem = std::tolower(elem);
        if (elem < 'a' || elem > 'z') elem = ' ';
    }

    return line;
}