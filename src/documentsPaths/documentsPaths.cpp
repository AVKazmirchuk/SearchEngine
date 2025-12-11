//
// Created by Alexander on 31.03.2025.
//



#include "documentsPaths.h"



const std::vector<std::string>& DocumentsPaths::getDocumentsPaths()
{
    return documentsPaths;
}

void DocumentsPaths::clearDocumentsPaths()
{
    documentsPaths.clear();
}

void DocumentsPaths::updateDocumentsPaths(const std::vector<std::string>& in_documentsPaths)
{
    documentsPaths = in_documentsPaths;
}

void DocumentsPaths::updateDocumentsPaths(std::vector<std::string>&& in_documentsPaths)
{
    documentsPaths = std::move(in_documentsPaths);
}