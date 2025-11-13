//
// Created by AKazmirchuk on 13.11.2025.
//



#include "DispatcherOperations.h"



const ErrorCode DispatcherOperations::convertErrorCodeFrom(const kav::ErrorCode errorCode)
{
    //Соответствие кодов ошибки внутреннего и внешнего
    const std::map<kav::ErrorCode, ErrorCode> matchingErrorCodes{

            {kav::ErrorCode::no_error,                       ErrorCode::no_error},
            {kav::ErrorCode::error_file_missing,             ErrorCode::error_file_missing},
            {kav::ErrorCode::error_file_not_open_read,       ErrorCode::error_file_not_open_read},
            {kav::ErrorCode::error_file_not_read,            ErrorCode::error_file_not_read},
            {kav::ErrorCode::error_file_not_open_write,      ErrorCode::error_file_not_open_write},
            {kav::ErrorCode::error_file_not_write,           ErrorCode::error_file_not_write},
            {kav::ErrorCode::error_json_structure_corrupted, ErrorCode::error_json_structure_corrupted},
            {kav::ErrorCode::error_json_structure_not_match, ErrorCode::error_json_structure_not_match},
            {kav::ErrorCode::error_array_empty,              ErrorCode::error_array_empty}

    };

    //Вернуть внутренний код ошибки
    return matchingErrorCodes.at(errorCode);
}

std::pair<int, int> DispatcherOperations::countNumberOfThreads(const std::vector<std::string> &filePaths, const unsigned int desiredNumberOfThreads)
{
    //Количество дополнительных потоков
    //Если количество документов меньше либо равно желаемого количества потоков - использовать количество потоков равным количеству документов.
    //В противном случае - использовать желаемое количество потоков.
    int numberOfThreads = filePaths.size() <= desiredNumberOfThreads ? filePaths.size() : desiredNumberOfThreads;

    //Определить разницу количества документов между потоками
    std::size_t difference{filePaths.size() / numberOfThreads};

    if (filePaths.size() % numberOfThreads)
    {
        //Увеличить количество потоков
        ++numberOfThreads;
    }

    return {difference, numberOfThreads};
}

std::size_t DispatcherOperations::countErrorsNumber(std::vector<ErrorCode> &errors)
{
    //Количество непрочитанных документов
    std::size_t errorNumber{};

    //Для каждого кода ошибки документов
    for (auto error : errors)
    {
        //Если при чтении произошла ошибка
        if (error != ErrorCode::no_error)
        {
            //Увеличить количество непрочитанных документов
            ++errorNumber;
        }
    }

    //Вернуть количество непрочитанных документов
    return errorNumber;
}

