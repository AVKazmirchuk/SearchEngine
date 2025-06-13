//
// Created by Alexander on 27.01.2024.
//

#ifndef SEARCH_ENGINE_CHECKFILEEXCEPTION_H
#define SEARCH_ENGINE_CHECKFILEEXCEPTION_H



#include <exception>
#include <map>
#include <string>

#include "errorCode.h"



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
