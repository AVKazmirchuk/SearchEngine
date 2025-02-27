//
// Created by Alexander on 15.02.2025.
//



#include "documents.h"



void Documents::updateDocuments(std::vector<std::string> in_documents)
{
    for (auto& document : in_documents)
    {
        documents.emplace_back(std::move(characterToLower(document)));
    }
}