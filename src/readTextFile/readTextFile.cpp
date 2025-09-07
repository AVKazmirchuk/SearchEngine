//
// Created by Alexander on 25.02.2025.
//



#include <future>
#include <list>
#include <vector>

//#include "boost/assert/source_location.hpp"

//#include "kav/operationFileAndJSON.h"
#include "dispatcherDetermineValidity.h"
#include "readTextFile.h"




std::vector<std::string> ReadTextFile::readTextFile(const std::vector<std::string>& filePaths)
{
    //Документы
    std::vector<std::string> documents;

    //Контейнер результатов потоков
    std::list<std::future<std::pair<std::string, ErrorCode>>> futures;

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        futures.push_back(std::async(DispatcherDetermineValidity::readTextFile, std::cref(filePaths[docID]), ErrorLevel::error, "", BOOST_CURRENT_LOCATION));
    }

    long int errorNumber{};

    try
    {
        //Ожидать завершение потоков
        for (auto &future: futures)
        {
            if (future.get().second != ErrorCode::no_error)
            {
                ++errorNumber;
            }

            //Добавить документ
            documents.push_back(future.get().first);

        }
    }
    catch (const std::exception& e)
    {
        throw;
    }

    if (errorNumber == filePaths.size())
    {

    }

    //Вернуть документы
    return documents;
}
