//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include <iostream>
#include <filesystem>

#include "kav/operationFileAndJSON.h"



kav::ErrorCode kav::OperationFileAndJSON::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth, const boost::source_location &callingFunction)
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

std::pair<kav::JSON, kav::ErrorCode> kav::OperationFileAndJSON::readJSONFile(const std::string& filePath, const boost::source_location &callingFunction)
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

        if (objectJSON.is_discarded()) errorCode = ErrorCode::error_json_structure_corrupted;
        else
        {
            return {objectJSON, errorCode};
        }
    }

    //else if ((objectJSON = JSON::parse(inFile, nullptr, false)).is_discarded()) errorCode = ErrorCode::error_json_structure_corrupted;
    //else if (inFile.fail()) errorCode = ErrorCode::error_file_not_read;

    return {objectJSON, errorCode};
}

std::pair<std::string, kav::ErrorCode> kav::OperationFileAndJSON::readTextFile(const std::string& filePath, const boost::source_location &callingFunction)
{
    //std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    std::string tmp{};


    ErrorCode errorCode{ErrorCode::no_error};

    if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::error_file_missing;
    else if (!inFile.is_open()) errorCode = ErrorCode::error_file_not_open_read;

    //Прочитать файл документа и вернуть документ
    if (errorCode == ErrorCode::no_error)
    {
        //system("disconnectDisk.bat");


        //std::string tmp;

        /*int i{};
        for (std::string word; inFile >> word; ++i)
        {
            tmp += word;
            if (i == 9)
            {
                //system("disconnectDisk.bat");
                //break;
            }
        }*/
        try
        {

            tmp = {(std::istreambuf_iterator<char>(inFile)), {}};
        }
        catch (const std::exception& e)
        {
            errorCode = ErrorCode::error_file_not_read;
            //std::cout << "Exception: " << e.what() << ". " << '\n' << "inFile: " << inFile.good() << " " << inFile.bad() << " " << inFile.fail() << " " << inFile.rdstate() << '\n';
        }

        //std::cout << '\n' << "inFile: " << inFile.good() << " " << inFile.bad() << " " << inFile.fail() << " " << inFile.rdstate() << '\n';

        //if (inFile.fail()) errorCode = ErrorCode::error_file_not_read;
    }

    return {tmp, errorCode};
}

kav::ErrorCode kav::OperationFileAndJSON::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                                        const boost::source_location &callingFunction)
{
    //std::cout << "checkJSONStructureMatch: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (!CheckJSON::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::error_json_structure_not_match;

    return errorCode;
}

kav::ErrorCode kav::OperationFileAndJSON::checkArray(const JSON& objectJSON, const boost::source_location &callingFunction)
{
    //std::cout << "checkArray: " << callingFunction.function_name() << std::endl;

    ErrorCode errorCode{ErrorCode::no_error};

    if (objectJSON.empty()) errorCode = ErrorCode::error_array_empty;

    return errorCode;
}



