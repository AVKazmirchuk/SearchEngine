//
// Created by Alexander on 15.02.2025.
//



#include "documents.h"



void Documents::updateDocuments(const std::vector<std::string>& in_documents)
{
    documents = in_documents;
}

void Documents::updateDocuments(std::vector<std::string>&& in_documents)
{
    documents = std::move(in_documents);
}