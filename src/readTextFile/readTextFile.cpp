//
// Created by Alexander on 25.02.2025.
//



#include <future>
#include <list>
#include <vector>

#include "dispatcherDetermineValidity.h"
#include "readTextFile.h"

/*
void ReadTextFile::checkAllFilesHaveErrors(const long int errorNumber, const std::vector<std::string>& filePaths)
{
    if (errorNumber == filePaths.size())
    {
        DispatcherDetermineValidity::checkAllFilesHaveErrors("", BOOST_CURRENT_LOCATION);
    }
}

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

    checkAllFilesHaveErrors(errorNumber, filePaths);

    //Вернуть документы
    return documents;
}
*/