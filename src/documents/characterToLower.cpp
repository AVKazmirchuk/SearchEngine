//
// Created by Alexander on 28.01.2025.
//



#include <iostream>
#include "documents.h"



std::string& Documents::characterToLower(std::string& line)
{
    for (auto& ch : line)
    {
        ch = std::tolower(ch);
        if (ch < 'a' || ch > 'z') ch = ' ';
    }

    return line;
}