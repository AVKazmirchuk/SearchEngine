//
// Created by Alexander on 31.03.2025.
//



#include <iostream>
#include <filesystem>
#include <list>

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
        KAV_SYSTEM_DISCONNECT_DISK

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
    std::pair<kav::JSON, kav::ErrorCode> objectJSON;

    //Обнулить код ошибки
    objectJSON.second = ErrorCode::no_error;

    //Если файл не существует - установить соответствующий код ошибки
    if (!std::filesystem::exists(filePath)) objectJSON.second = ErrorCode::error_file_missing;
    //В противном случае, если файл не открыт - установить соответствующий код ошибки
    else if (!inFile.is_open()) objectJSON.second = ErrorCode::error_file_not_open_read;

    //Если ошибки нет
    if (objectJSON.second == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время чтения раскомментировать
        KAV_SYSTEM_DISCONNECT_DISK

        try
        {
            //Читать файл
            objectJSON.first = JSON::parse(inFile, nullptr, false);
        }
        catch (const std::exception& e)
        {
            //Если при чтении произошла ошибка - установить соответствующий код ошибки
            objectJSON.second = ErrorCode::error_file_not_read;
        }

        //Если структура JSON-объекта повреждена - установить соответствующий код ошибки
        if (objectJSON.first.is_discarded()) objectJSON.second = ErrorCode::error_json_structure_corrupted;
    }

    //Вернуть пару JSON-объекта и кода ошибки
    return objectJSON;
}

std::pair<std::string, kav::ErrorCode> kav::OperationFileAndJSON::readTextFile(const std::string& filePath)
{
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    //Подготовить документ для записи
    std::pair<std::string, kav::ErrorCode> tmp;

    //Обнулить код ошибки
    tmp.second = ErrorCode::no_error;

    //Если файл не существует - установить соответствующий код ошибки
    if (!std::filesystem::exists(filePath)) tmp.second = ErrorCode::error_file_missing;
    //В противном случае, если файл не открыт - установить соответствующий код ошибки
    else if (!inFile.is_open()) tmp.second = ErrorCode::error_file_not_open_read;

    //Если ошибки нет
    if (tmp.second == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время чтения раскомментировать
        KAV_SYSTEM_DISCONNECT_DISK

        try
        {
            //Читать файл
            tmp.first = {(std::istreambuf_iterator<char>(inFile)), {}};
        }
        catch (const std::exception& e)
        {
            //Если при чтении произошла ошибка - установить соответствующий код ошибки
            tmp.second = ErrorCode::error_file_not_read;
        }
    }

    //Вернуть пару текста и кода ошибки
    return tmp;
}

std::pair<std::string, kav::ErrorCode> kav::OperationFileAndJSON::readLastLineFromTextFile(const std::string &filePath)
{
    //Создать объект для чтения файла документа. Открытие в обычном режиме приводит к неочевидным результатам (появляются дополнительные символы).
    //Но открытие в бинарном формате приводит к совсем неочевидным результатам (строка отображается верно, но сравнение с шаблоном не проходит).
    std::ifstream inFile(filePath);

    //Подготовить документ для записи
    std::pair<std::string, kav::ErrorCode> tmp;

    //Обнулить код ошибки
    tmp.second = ErrorCode::no_error;

    //Если файл не существует - установить соответствующий код ошибки
    if (!std::filesystem::exists(filePath)) tmp.second = ErrorCode::error_file_missing;
        //В противном случае, если файл не открыт - установить соответствующий код ошибки
    else if (!inFile.is_open()) tmp.second = ErrorCode::error_file_not_open_read;

    //Если ошибки нет
    if (tmp.second == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время чтения раскомментировать
        KAV_SYSTEM_DISCONNECT_DISK

        //Читать последнюю строку

        //Передвинуть указатель, чтобы прочитать последний символ
        inFile.seekg(-1, std::ios::end);

        char ch;
        //Прочитать последний символ
        inFile.get(ch);
        //Если прочитан символ новой строки - перейти на чтение последнего символа
        if (ch == '\n') inFile.seekg(-3, std::ios::cur);
            //Перейти на чтение последнего символа
        else inFile.seekg(-1, std::ios::cur);

        //Пока читается
        while (inFile.get(ch))
        {
            //Если прочитанный символ новой строки - указатель стоит в начале строки
            if (ch == '\n') break;
                //Если указатель на второй позиции
            else if (inFile.tellg() == 1)
            {
                //Перейти на начало строки
                inFile.seekg(-1, std::ios::cur);
                break;
            }

            //Перейти для чтения предыдущего символа
            inFile.seekg(-2, std::ios::cur);
        }

        //Прочитать строку целиком
        std::getline(inFile, tmp.first);

        //Если при чтении произошла ошибка
        if (inFile.fail())
        {
            //Установить соответствующий код ошибки
            tmp.second = ErrorCode::error_file_not_read;
        }
    }

    //Вернуть пару текста и кода ошибки
    return tmp;
}

std::pair<std::string, kav::ErrorCode> kav::OperationFileAndJSON::readFirstLineFromTextFile(const std::string &filePath)
{
    //Создать объект для чтения файла документа.
    std::ifstream inFile(filePath);

    //Подготовить документ для записи
    std::pair<std::string, kav::ErrorCode> tmp;

    //Обнулить код ошибки
    tmp.second = ErrorCode::no_error;

    //Если файл не существует - установить соответствующий код ошибки
    if (!std::filesystem::exists(filePath)) tmp.second = ErrorCode::error_file_missing;
        //В противном случае, если файл не открыт - установить соответствующий код ошибки
    else if (!inFile.is_open()) tmp.second = ErrorCode::error_file_not_open_read;

    //Если ошибки нет
    if (tmp.second == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время чтения раскомментировать
        KAV_SYSTEM_DISCONNECT_DISK

        //Читать последнюю строку

        //Прочитать строку целиком
        std::getline(inFile, tmp.first);

        //Если при чтении произошла ошибка
        if (inFile.fail())
        {
            //Установить соответствующий код ошибки
            tmp.second = ErrorCode::error_file_not_read;
        }
    }

    //Вернуть пару текста и кода ошибки
    return tmp;
}

kav::ErrorCode kav::OperationFileAndJSON::writeTextFile(const std::string &filePath, const std::string &text, std::ios_base::openmode openMode)
{
    //Создать объект для записи
    std::ofstream outFile(filePath, openMode);

    //Обнулить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};

    //Если файл не открыт - установить соответствующий код ошибки
    if (!outFile.is_open()) errorCode = ErrorCode::error_file_not_open_write;

    //Если ошибки нет
    if (errorCode == ErrorCode::no_error)
    {
        //Для прохождения теста на эмуляцию ошибки во время записи раскомментировать
        KAV_SYSTEM_DISCONNECT_DISK

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



//Для тестирования передачи контейнера по ссылке
/*void kav::OperationFileAndJSON::readTextFileRef(const std::string &filePath, std::string &document, ErrorCode &errorCode)
{
    //Создать объект для чтения файла документа
    std::ifstream inFile(filePath);

    //Подготовить документ для записи
    //std::string tmp{};

    //Обнулить код ошибки
    errorCode = ErrorCode::no_error;

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
            document = {(std::istreambuf_iterator<char>(inFile)), {}};

        }
        catch (const std::exception& e)
        {
            //Если при чтении произошла ошибка - установить соответствующий код ошибки
            errorCode = ErrorCode::error_file_not_read;
        }
    }
}*/