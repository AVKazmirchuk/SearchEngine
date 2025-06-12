//
// Created by Alexander on 27.01.2024.
//

#ifndef SEARCH_ENGINE_CHECKFILEEXCEPTION_H
#define SEARCH_ENGINE_CHECKFILEEXCEPTION_H



#include <exception>
#include <map>


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

const std::map<ErrorCode, std::string> descriptionErrorCode{

                {ErrorCode::no_error, ""},
                {ErrorCode::error_file_missing, "This file is missing"},
                {ErrorCode::error_file_not_open_read, "This file cannot be opened for reading"},
                {ErrorCode::error_file_not_open_write, "This file cannot be opened for writing"},
                {ErrorCode::error_json_structure_corrupted, "The structure of this file is corrupted"},
                {ErrorCode::error_json_structure_not_match, "The structure of this file does not match the required one"},
                {ErrorCode::error_file_paths_array_empty, "The array of this file paths is empty"},
                {ErrorCode::error_requests_array_empty, "The query array of this file is empty"}

};

/**
 * Класс реализует генерацию исключений
 */
class CheckFileException : public std::exception
{

public:

    /**
     * Инициализирует код исключения
     * @param in_errorCode Код исключения
     * @param in_information Информация по исключению
     */
    explicit CheckFileException(ErrorCode in_errorCode, const std::string& in_information = "") : errorCode(in_errorCode)
    {
        /*switch (errorCode)
        {
            case ErrorCode::error_file_missing :
                information += "This file is missing: ";
                break;
            case ErrorCode::error_file_not_open_read :
                information += "This file cannot be opened for reading: ";
                break;
            case ErrorCode::error_file_not_open_write :
                information += "This file cannot be opened for writing: ";
                break;
            case ErrorCode::error_json_structure_corrupted :
                information += "The structure of this file is corrupted: ";
                break;
            case ErrorCode::error_json_structure_not_match :
                information += "The structure of this file does not match the required one: ";
                break;
            case ErrorCode::error_file_paths_array_empty :
                information += "The array of this file paths is empty: ";
                break;
            case ErrorCode::error_requests_array_empty :
                information += "The query array of this file is empty: ";
                break;
        }*/


        information = descriptionErrorCode.at(errorCode) + ": " + in_information + '.';
    }

    /**
     * Получить информацию по исключению
     * @return Информация по исключению
     */
    [[nodiscard]] const char* what() const noexcept override
    {
        return information.c_str();
    }

    /**
     * Получить код исключения
     * @return Код исключения
     */
    [[nodiscard]] ErrorCode getErrorCode() const
    {
        return errorCode;
    }

private:

    ErrorCode errorCode;
    std::string information;

};



#endif //SEARCH_ENGINE_CHECKFILEEXCEPTION_H
