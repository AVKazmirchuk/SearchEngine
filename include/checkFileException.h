//
// Created by Alexander on 27.01.2024.
//

#ifndef SEARCH_ENGINE_CHECKFILEEXCEPTION_H
#define SEARCH_ENGINE_CHECKFILEEXCEPTION_H



#include <iostream>
#include <exception>
#include <string>



enum class ErrorCode
{
    ERROR_FILE_MISSING = 1,
    ERROR_FILE_STRUCTURE_CORRUPTED,
    ERROR_FILE_STRUCTURE_NOT_MATCH,
    ERROR_FILE_PATHS_ARRAY_EMPTY,
    ERROR_REQUESTS_ARRAY_EMPTY
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
        switch (errorCode)
        {
            case ErrorCode::ERROR_FILE_MISSING :
                information += "This file is missing: ";
                break;
            case ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED :
                information += "The structure of this file is corrupted: ";
                break;
            case ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH :
                information += "The structure of this file does not match the required one: ";
                break;
            case ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY :
                information += "The array of file paths is empty: ";
                break;
            case ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY :
                information += "The query array is empty: ";
                break;
        }

        information += in_information;
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
    std::string information{"ERROR: "};
};



#endif //SEARCH_ENGINE_CHECKFILEEXCEPTION_H
