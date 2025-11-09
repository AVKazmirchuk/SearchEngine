//
// Created by Alexander on 31.03.2025.
//



#include <algorithm>
#include <iostream>
#include <filesystem>
#include <future>
#include <list>
#include <thread>

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
        //system("disconnectDisk.bat");

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
        //system("disconnectDisk.bat");

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

std::pair<std::vector<std::string>, std::vector<kav::ErrorCode>> kav::OperationFileAndJSON::readMultipleTextFiles(const std::vector<std::string> &filePaths, const unsigned int desiredNumberOfThreads)
{
    /*
     * Чтение документов в нескольких потоках
     */

    /*
    //Контейнер прочитанных документов
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents;

    //Если количество документов меньше либо равно желаемого количества потоков - использовать количество потоков равным количеству документов.
    //В противном случае - использовать желаемое количество потоков.
    int numberOfThreads = filePaths.size() <= desiredNumberOfThreads ? filePaths.size() : desiredNumberOfThreads;

    //Определить разницу количества документов между потоками
    std::size_t difference{filePaths.size() / numberOfThreads};

    if (filePaths.size() % numberOfThreads)
    {
        ++numberOfThreads;
    }

    //Контейнер результатов потоков
    std::list<std::future<std::pair<std::vector<std::string>, std::vector<ErrorCode>>>> futures(numberOfThreads);


    std::size_t beginDocID{};

    //Для каждого будущего потока
    for (auto &future : futures)
    {
        std::size_t endDocID{beginDocID + difference - 1};

        if (endDocID >= filePaths.size()) endDocID = filePaths.size() - 1;

        //std::cout << "beginDocID: " << beginDocID << ", endDocID: " << endDocID << '\n';

        //Запустить чтение файлов в своём диапазоне
        future = std::async(
                [beginDocID = beginDocID, endDocID = endDocID, &filePaths]()
            {
                //Контейнер пар прочитанных документов и кодов ошибок
                std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents;

                //Для каждого документа
                for (std::size_t currentDocID{beginDocID}; currentDocID <= endDocID; ++currentDocID)
                    {
                        //Запустить чтение из файла
                        std::pair<std::string, ErrorCode> tmp{readTextFile(filePaths[currentDocID])};

                        //Добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
                        documents.first.push_back(std::move(tmp.first));
                        //Добавить код ошибки
                        documents.second.push_back(tmp.second);
                    }

                //Вернуть контейнер пар прочитанных документов и кодов ошибок
                return documents;
            }
        );

        beginDocID = endDocID + 1;
    }

    try
    {
        //Ожидать завершение потоков
        for (auto &future : futures)
        {
            //Получить результат работы потока
            std::pair<std::vector<std::basic_string<char>>, std::vector<ErrorCode>> tmp{future.get()};

            //Для каждого документа
            for (std::size_t docID{}; docID < filePaths.size(); ++docID)
            {
                //Добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
                documents.first.push_back(std::move(tmp.first[docID]));
                //documents.first = std::move(tmp.first);
                //Добавить код ошибки
                documents.second.push_back(tmp.second[docID]);
            }
        }
    }
    catch (const std::exception& e)
    {
        //Регенерировать исключение выше. Будет обработано в главной функции
        throw;
    }//Чтение документов в нескольких потоках*/

    /*
     * Чтение документов в одном потоке
     */


    //Контейнер прочитанных документов
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents;

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        std::pair<std::string, ErrorCode> tmp{kav::OperationFileAndJSON::readTextFile(filePaths[docID])};

        //Добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
        documents.first.push_back(std::move(tmp.first));
        //Добавить код ошибки
        documents.second.push_back(tmp.second);
    }//Чтение документов в одном потоке*/

    //Вернуть пару контейнера текстов и кода ошибки
    return documents;
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