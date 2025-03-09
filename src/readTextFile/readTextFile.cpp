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



std::string ReadTextFile::readTextFile(const std::string& filePath)
{
    std::ifstream file(filePath);

    return {(std::istreambuf_iterator<char>(file)), {}};
}

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
        asyncs.emplace_back(std::async(
                static_cast<std::string(ReadTextFile::*)(const std::string&)>(&ReadTextFile::readTextFile), this,
                std::cref(filePaths[docID])));
    }

    try
    {
        //Ожидать завершение потоков
        for (auto &async: asyncs)
        {
            //Добавить документ
            documents.emplace_back(async.get());
        }
    }
    catch (const std::exception& e)
    {
        Logger().fatal("EXCEPTION: " + std::string(e.what()));
        exitProgram();

    }

    return documents;
}