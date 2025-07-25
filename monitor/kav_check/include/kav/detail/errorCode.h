//
// Created by Alexander on 13.06.2025.
//

#ifndef SEARCH_ENGINE_ERRORCODE_H
#define SEARCH_ENGINE_ERRORCODE_H



namespace kav
{

    enum class ErrorCode
    {
        no_error,
        error_file_missing,
        error_file_not_open_read,
        error_file_not_open_write,
        error_json_structure_corrupted,
        error_json_structure_not_match,
        error_file_paths_array_empty,
        error_requests_array_empty
    };

    static const std::map<ErrorCode, std::string> descriptionErrorCode{

            {ErrorCode::no_error,                       ""},
            {ErrorCode::error_file_missing,             "This file is missing"},
            {ErrorCode::error_file_not_open_read,       "This file cannot be opened for reading"},
            {ErrorCode::error_file_not_open_write,      "This file cannot be opened for writing"},
            {ErrorCode::error_json_structure_corrupted, "The structure of this file is corrupted"},
            {ErrorCode::error_json_structure_not_match, "The structure of this file does not match the required one"},
            {ErrorCode::error_file_paths_array_empty,   "The array of this file paths is empty"},
            {ErrorCode::error_requests_array_empty,     "The query array of this file is empty"}

    };

}

#endif //SEARCH_ENGINE_ERRORCODE_H
