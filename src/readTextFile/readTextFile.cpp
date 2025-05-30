//
// Created by Alexander on 25.02.2025.
//



#include <fstream>
#include <vector>
#include <future>
#include <list>
#include <source_location>

#include "readTextFile.h"
#include "general.h"
#include "logger.h"
#include "checkFile.h"



std::vector<std::string> ReadTextFile::readTextFile(const std::vector<std::string>& filePaths, const std::source_location &callingFunction)
{
    //Документы
    std::vector<std::string> documents;

    //Контейнер результатов потоков
    std::list<std::future<std::string>> futures;

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        futures.push_back(std::async(
                [&callingFunction](const std::string& filePath) -> std::string
        {
            //Создать объект для чтения файла документа
            std::ifstream inFile(filePath);

            //Проверить файл на открытие для чтения
            //if (!inFile.is_open())
            //{
            //    Logger::fatal("std::vector<std::string> ReadTextFile::readTextFile(const std::vector<std::string>& filePaths)",
            //                  CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath));
            //    throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath);
            //}

            //CheckFile::isFileOpenRead(inFile, filePath,
            //                          "std::vector<std::string> ReadTextFile::readTextFile(const std::vector<std::string>& filePaths)", std::runtime_error("e"));
            std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;
            DispatcherOperationValidity::determineReadFile(inFile, filePath, callingFunction.function_name());

            //Прочитать файл документа и вернуть документ
            return {(std::istreambuf_iterator<char>(inFile)), {}};
        },
        std::cref(filePaths[docID]))
        );
    }

    try
    {
        //Ожидать завершение потоков
        for (auto &future: futures)
        {
            //Добавить документ
            documents.push_back(future.get());
        }
    }
    catch (const std::exception& e)
    {
        //Logger::fatal("EXCEPTION: " + std::string(e.what()));
        //exitProgram();
        throw;
    }

    //Вернуть документы
    return documents;
}
