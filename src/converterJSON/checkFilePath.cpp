//
// Created by Alexander on 07.03.2025.
//



#include "converterJSON.h"
#include "checkFileException.h"
#include "logger.h"



void ConverterJSON::checkFilePath()
{

    if (configJSON[ConfigConverterJSON::filesStr].empty())
    {
        Logger::fatal("void ConverterJSON::checkFilePath()", CheckFileException(ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY));
        throw CheckFileException(ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY);
    }

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