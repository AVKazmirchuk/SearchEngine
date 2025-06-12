//
// Created by Alexander on 07.03.2025.
//



#include "converterJSON.h"
#include "checkFileException.h"
#include "logger.h"
#include "operationFileAndJSON.h"


void ConverterJSON::checkFilePath()
{

    DispatcherDetermineValidity::checkFilePathsArray(configJSON[ConfigConverterJSON::filesStr]);

    /*for (std::size_t idx{}; idx < configJSON[ConfigConverterJSON::filesStr].size(); ++idx)
    {
        if (!std::filesystem::exists(configJSON[ConfigConverterJSON::filesStr][idx]))
        {
            auto missingFile = configJSON[ConfigConverterJSON::filesStr][idx];

            configJSON[ConfigConverterJSON::filesStr].erase(idx);
            --idx;
            Logger::error("File " + std::string(missingFile) + " is missing!");
        }
    }*/

}

void ConverterJSON::checkRequests()
{
    DispatcherDetermineValidity::checkRequestsArray(requestsJSON[ConfigConverterJSON::requestsStr]);
}