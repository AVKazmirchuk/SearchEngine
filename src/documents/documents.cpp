//
// Created by Alexander on 31.03.2025.
//



#include "documents.h"



const std::vector<std::string>& Documents::getDocuments()
{
    return documents;
}

void Documents::clearDocuments()
{
    documents.clear();
}

void Documents::updateDocuments(const std::vector<std::string>& in_documents)
{
    documents = in_documents;
}

void Documents::updateDocuments(std::vector<std::string>&& in_documents)
{
    documents = std::move(in_documents);
}