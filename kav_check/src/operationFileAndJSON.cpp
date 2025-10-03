//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include <iostream>
#include <filesystem>

#include "kav/operationFileAndJSON.h"



kav::ErrorCode kav::OperationFileAndJSON::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth)
{
    //Создать объект для записи
    std::ofstream outFile(filePath);

    //Обнулить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};

    //Если файл не открыт - установить соответствующий код ошибки
    if (!outFile.is_open()) errorCode = ErrorCode::error_file_not_open_write;

    //Если ошибки нет
    if (errorCode == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время записи раскомментировать
        //system("disconnectDisk.bat");

        //Записать JSON-объект в файл
        outFile << std::setw(formatByWidth) << objectJSON;

        //Закрыть файл
        outFile.close();

        //Если были ошибки во время записи - установить соответствующий код ошибки
        if (outFile.fail()) errorCode = ErrorCode::error_file_not_write;
    }

    //Вернуть код ошибки
    return errorCode;
}

std::pair<kav::JSON, kav::ErrorCode> kav::OperationFileAndJSON::readJSONFile(const std::string& filePath)
{
    //Создать объект для чтения
    std::ifstream inFile(filePath);

    //Подготовить JSON-объект для записи
    JSON objectJSON;

    //Обнулить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};

    //Если файл не существует - установить соответствующий код ошибки
    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    //В противном случае, если файл не открыт - установить соответствующий код ошибки
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;

    //Если ошибки нет
    if (errorCode == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время чтения раскомментировать
        //system("disconnectDisk.bat");

        try
        {
            //Читать файл
            objectJSON = JSON::parse(inFile, nullptr, false);
        }
        catch (const std::exception& e)
        {
            //Если при чтении произошла ошибка - установить соответствующий код ошибки
            errorCode = ErrorCode::error_file_not_read;
        }

        //Если структура JSON-объекта повреждена - установить соответствующий код ошибки
        if (objectJSON.is_discarded()) errorCode = ErrorCode::error_json_structure_corrupted;
    }

    //Вернуть пару JSON-объекта и кода ошибки
    return {objectJSON, errorCode};
}

std::pair<std::string, kav::ErrorCode> kav::OperationFileAndJSON::readTextFile(const std::string& filePath)
{
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    //Подготовить документ для записи
    std::string tmp{};

    //Обнулить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};

    //Если файл не существует - установить соответствующий код ошибки
    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    //В противном случае, если файл не открыт - установить соответствующий код ошибки
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;

    //Если ошибки нет
    if (errorCode == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время чтения раскомментировать
        //system("disconnectDisk.bat");

        try
        {
            //Читать файл
            tmp = {(std::istreambuf_iterator<char>(inFile)), {}};
        }
        catch (const std::exception& e)
        {
            //Если при чтении произошла ошибка - установить соответствующий код ошибки
            errorCode = ErrorCode::error_file_not_read;
        }
    }

    //Пара текста и кода ошибки
    return {tmp, errorCode};
}

kav::ErrorCode kav::OperationFileAndJSON::writeTextFile(const std::string &filePath, const std::string &text, std::ios_base::openmode openModeFile)
{
    //Создать объект для записи
    std::ofstream outFile(filePath, openModeFile);

    //Обнулить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};

    //Если файл не открыт - установить соответствующий код ошибки
    if (!outFile.is_open()) errorCode = ErrorCode::error_file_not_open_write;

    //Если ошибки нет
    if (errorCode == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время записи раскомментировать
        //system("disconnectDisk.bat");

        //Записать текст в файл
        outFile << text;

        //Закрыть файл
        outFile.close();

        //Если были ошибки во время записи - установить соответствующий код ошибки
        if (outFile.fail()) errorCode = ErrorCode::error_file_not_write;
    }

    //Вернуть код ошибки
    return errorCode;
}

kav::ErrorCode kav::OperationFileAndJSON::checkJSONStructureMatch(const JSON& objectJSON, const JSON& objectJSONTemplate)
{
    //Обнулить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};

    //Если JSON-структура не соответствует шаблону - установить соответствующий код ошибки
    if (!CheckJSON::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::error_json_structure_not_match;

    //Вернуть код ошибки
    return errorCode;
}

kav::ErrorCode kav::OperationFileAndJSON::checkArray(const JSON& objectJSON)
{
    //Обнулить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};

    //Если массив JSON-объекта пуст - установить соответствующий код ошибки
    if (objectJSON.empty()) errorCode = ErrorCode::error_array_empty;

    //Вернуть код ошибки
    return errorCode;
}



