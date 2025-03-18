//
// Created by Alexander on 07.03.2025.
//



#include "converterJSON.h"
#include "checkFileException.h"



void ConverterJSON::checkFilePath()
{
    for (std::size_t idx{}; idx < configJSON[constants::filesStr].size(); ++idx)
    {
        if (!std::filesystem::exists(configJSON[constants::filesStr][idx]))
        {
            auto missingFile{configJSON[constants::filesStr][idx]};
            configJSON[constants::filesStr].erase(idx);
            --idx;
            Logger().error("File " + std::string(missingFile) + " is missing!");
        }
    }

    if (configJSON[constants::filesStr].empty())
    {
        Logger().fatal("The array of file paths is empty!");
        throw CheckFileException(ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY);
    }
}