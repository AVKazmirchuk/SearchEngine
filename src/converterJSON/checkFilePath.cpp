//
// Created by Alexander on 07.03.2025.
//



#include "converterJSON.h"
#include "exceptions.h"



void ConverterJSON::checkFilePath()
{
    for (std::size_t idx{}; idx < configJSON[constants::filesStr].size(); ++idx)
    {
        if (!std::filesystem::exists(configJSON[constants::filesStr][idx]))
        {
            auto missingFile{configJSON[constants::filesStr][idx]};
            configJSON[constants::filesStr].erase(idx);
            --idx;
            std::cout << '\n' << "File " << missingFile << " is missing!" << '\n';
        }
    }

    if (configJSON[constants::filesStr].empty())
    {
        std::cout << '\n' << "The array of file paths is empty!" << '\n';
        throw CheckFileException(ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY);
    }
}