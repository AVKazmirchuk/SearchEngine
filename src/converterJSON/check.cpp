//
// Created by Alexander on 07.03.2025.
//



#include "converterJSON.h"
#include "checkFileException.h"
#include "logger.h"
#include "checkFile.h"


void ConverterJSON::checkFilePath(const std::source_location &callingFunction)
{

    std::cout << "checkFilePath: " << callingFunction.function_name() << std::endl;
    DispatcherOperationValidity::determineFilePathsArrayEmpty(configJSON[ConfigConverterJSON::filesStr], callingFunction.function_name());

    for (std::size_t idx{}; idx < configJSON[ConfigConverterJSON::filesStr].size(); ++idx)
    {
        if (!std::filesystem::exists(configJSON[ConfigConverterJSON::filesStr][idx]))
        {
            auto missingFile = configJSON[ConfigConverterJSON::filesStr][idx];

            configJSON[ConfigConverterJSON::filesStr].erase(idx);
            --idx;
            Logger::error("File " + std::string(missingFile) + " is missing!");
        }
    }

}

void ConverterJSON::checkRequests(const std::source_location &callingFunction)
{
    std::cout << "checkRequests: " << callingFunction.function_name() << std::endl;
    DispatcherOperationValidity::determineRequestsArrayEmpty(requestsJSON[ConfigConverterJSON::requestsStr], callingFunction.function_name());
}