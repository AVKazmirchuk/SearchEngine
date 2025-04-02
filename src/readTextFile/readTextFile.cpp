//
// Created by Alexander on 25.02.2025.
//



#include <fstream>
#include <iostream>
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
    std::list<std::future<std::string>> asyncs;

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        asyncs.push_back(std::async(
                [](const std::string& filePath) -> std::string
        {
            //Создать объект для чтения файла документа
            std::ifstream file(filePath);
            //Прочитать файл документа и вернуть документ
            return {(std::istreambuf_iterator<char>(file)), {}};
        },
        std::cref(filePaths[docID]))
        );
    }

    try
    {
        //Ожидать завершение потоков
        for (auto &async: asyncs)
        {
            //Добавить документ
            documents.push_back(std::move(async.get()));
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
