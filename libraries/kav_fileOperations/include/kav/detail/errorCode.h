//
// Created by Alexander on 13.06.2025.
//

#ifndef kav_fileOperations_ERRORCODE_H
#define kav_fileOperations_ERRORCODE_H



#include <map>
#include <string>



namespace kav
{

    /**
     * Коды ошибок работы с файлами
     */
    enum class ErrorCode
    {
        no_error,
        error_file_missing,
        error_file_not_open_read,
        error_file_not_read,
        error_file_not_open_write,
        error_file_not_write,
        error_json_structure_corrupted,
        error_json_structure_not_match,
        error_array_empty
    };

    /**
     * Класс описания кодов ошибок
     */
    class DescriptionErrorCode
    {

    public:

        DescriptionErrorCode() = delete;

        /**
         * Прочитать описание кодов ошибок
         * @return Ссылка на описание
         */
        static const std::string &descriptionErrorCode(const ErrorCode errorCode)
        {
            static const std::map<ErrorCode, std::string> varDescriptionErrorCode{

                    {ErrorCode::no_error,                       ""},
                    {ErrorCode::error_file_missing,             "This file is missing"},
                    {ErrorCode::error_file_not_open_read,       "This file cannot be opened for reading"},
                    {ErrorCode::error_file_not_read,            "This file has not been read"},
                    {ErrorCode::error_file_not_open_write,      "This file cannot be opened for writing"},
                    {ErrorCode::error_file_not_write,           "This file has not been write"},
                    {ErrorCode::error_json_structure_corrupted, "The structure of this file is corrupted"},
                    {ErrorCode::error_json_structure_not_match, "The structure of this file does not match the required one"},
                    {ErrorCode::error_array_empty,              "The array is empty"}
            };

            return varDescriptionErrorCode.at(errorCode);
        }

    };

}

#endif //kav_fileOperations_ERRORCODE_H
