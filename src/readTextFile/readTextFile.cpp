//
// Created by Alexander on 25.02.2025.
//



#include <fstream>
#include <vector>
#include <future>
#include <list>

#include "readTextFile.h"
#include "general.h"
#include "logger.h"



std::vector<std::string> ReadTextFile::readTextFile(const std::vector<std::string>& filePaths)
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
                [](const std::string& filePath) -> std::string
        {
            //Создать объект для чтения файла документа
            std::ifstream file(filePath);

            //Проверить файл на открытие для чтения
            if (!file.is_open())
            {
                Logger::fatal("std::vector<std::string> ReadTextFile::readTextFile(const std::vector<std::string>& filePaths)", CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath));
                throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath);
            }

            //Прочитать файл документа и вернуть документ
            return {(std::istreambuf_iterator<char>(file)), {}};
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
        Logger::fatal("EXCEPTION: " + std::string(e.what()));
        exitProgram();

    }

    //Вернуть документы
    return documents;
}
