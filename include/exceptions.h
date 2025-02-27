//
// Created by Alexander on 27.01.2024.
//

#ifndef SEARCH_ENGINE_EXCEPTIONS_H
#define SEARCH_ENGINE_EXCEPTIONS_H

#include <exception>
#include <string>

enum class ErrorCode
{
    ERROR_FILE_PATH_EMPTY = 1,
    ERROR_FILE_MISSING,
    ERROR_FILE_STRUCTURE_CORRUPTED,
    ERROR_FILE_EMPTY

};

class CheckFileException : public std::exception
{
private:
    std::string information{"ERROR: "};
    ErrorCode errorCode;
public:
    CheckFileException(ErrorCode in_errorCode, const std::string& in_information) : errorCode(in_errorCode)
    {
        switch (errorCode)
        {
            case ErrorCode::ERROR_FILE_PATH_EMPTY :
                information += "";
                break;
            case ErrorCode::ERROR_FILE_MISSING :
                information += "This file is missing: ";
                break;
            case ErrorCode::ERROR_FILE_EMPTY :
                information += "This file is empty: ";
                break;
            case ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED :
                information += "The structure of this file is corrupted: ";
                break;
        }

        information += in_information;
    }

    const char* what() const noexcept override
    {
        return information.c_str();
    }

    ErrorCode getErrorCode() const
    {
        return errorCode;
    }
};

#endif //SEARCH_ENGINE_EXCEPTIONS_H
