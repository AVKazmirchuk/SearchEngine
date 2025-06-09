//
// Created by Alexander on 25.02.2025.
//



#include <fstream>
#include <vector>
#include <future>
#include <list>

#include "boost/assert/source_location.hpp"
#include "boost/current_function.hpp"
#include "readTextFile.h"
#include "general.h"
#include "logger.h"

#include "operationValidity.h"



std::vector<std::string> ReadTextFile::readTextFile(const std::vector<std::string>& filePaths)
{
    //Документы
    std::vector<std::string> documents;

    //Контейнер результатов потоков
    std::list<std::future<tl::expected<std::string, ErrorCode>>> futures;

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        futures.push_back(std::async(OperationValidity::readTextFile, std::cref(filePaths[docID]), ErrorLevel::fatal, "", BOOST_CURRENT_LOCATION));
                //[&message, &errorLevel, &callingFunction](const std::string& filePath) -> std::string
        //{

            //Создать объект для чтения файла документа
            //std::ifstream inFile(filePath);

            //std::cout << "readTextFile: " << callingFunction.function_name() << std::endl;
            //DispatcherOperationValidity::determineReadFile(filePath, inFile, message, errorLevel, callingFunction);

            //Прочитать файл документа и вернуть документ
            //return {(std::istreambuf_iterator<char>(inFile)), {}};
        //},
        //std::cref(filePaths[docID]))
        //));
    }

    try
    {
        //Ожидать завершение потоков
        for (auto &future: futures)
        {
            //Добавить документ
            documents.push_back(future.get().value());
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
