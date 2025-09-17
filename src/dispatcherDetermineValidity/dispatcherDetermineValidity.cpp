//
// Created by Alexander on 13.06.2025.
//



#include "dispatcherDetermineValidity.h"



ErrorCode DispatcherDetermineValidity::writeJSONFile(const std::string& filePath, const JSON& objectJSON, ErrorLevel errorLevel,
                                                     const std::string& message, const int formatByWidth, const boost::source_location &callingFunction)
{

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::writeJSONFile(filePath, objectJSON, formatByWidth)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

std::pair<JSON, ErrorCode> DispatcherDetermineValidity::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                     const std::string& message,
                                                                     const boost::source_location &callingFunction)
{

    std::pair<JSON, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readJSONFile(filePath)};

    std::pair<JSON, ErrorCode> tmp{std::move(tmpOriginal.first), convertErrorCodeFrom(tmpOriginal.second)};

    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    return tmp;

}

std::pair<std::string, ErrorCode> DispatcherDetermineValidity::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                            const std::string& message,
                                                                            const boost::source_location &callingFunction)
{

    std::pair<std::string, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readTextFile(filePath)};

    std::pair<std::string, ErrorCode> tmp{std::move(tmpOriginal.first), convertErrorCodeFrom(tmpOriginal.second)};

    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    return tmp;
}

ErrorCode DispatcherDetermineValidity::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                                               ErrorLevel errorLevel, const std::string& message,
                                                               const boost::source_location &callingFunction)
{

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkJSONStructureMatch(objectJSON, objectJSONTemplate)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkFilePathsArray(JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                           const boost::source_location &callingFunction)
{

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkArray(objectJSON)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    if (errorCode == ErrorCode::error_array_empty)
    {
        errorCode = ErrorCode::error_file_paths_array_empty;
    }

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

ErrorCode DispatcherDetermineValidity::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                          const boost::source_location &callingFunction)
{

    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkArray(objectJSON)};

    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};

    if (errorCode == ErrorCode::error_array_empty)
    {
        errorCode = ErrorCode::error_requests_array_empty;
    }

    determineValidity("", errorCode, errorLevel, message, callingFunction);

    return errorCode;
}

std::pair<std::vector<std::string>, ErrorCode> DispatcherDetermineValidity::readMultipleTextFiles(const std::vector<std::string> &filePaths, ErrorLevel errorLevel, const std::string& message,
                                                                                                  const boost::source_location &callingFunction)
{
    //Документы
    std::vector<std::string> documents;

    //Контейнер результатов потоков
    std::list<std::future<std::pair<std::string, ErrorCode>>> futures;

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        //futures.push_back(std::async(DispatcherDetermineValidity::readTextFile, std::cref(filePaths[docID])));
        futures.push_back(std::async(DispatcherDetermineValidity::readTextFile, std::cref(filePaths[docID]), ErrorLevel::error, "", BOOST_CURRENT_LOCATION));
    }

    std::size_t errorNumber{};

    try
    {
        //Ожидать завершение потоков
        for (auto &future: futures)
        {
            std::pair<std::string, ErrorCode> tmp{future.get()};

            //Добавить документ
            documents.push_back(tmp.first);

            if (tmp.second != ErrorCode::no_error)
            {
                ++errorNumber;
            }
        }
    }
    catch (const std::exception& e)
    {
        throw;
    }

    ErrorCode errorCode{ErrorCode::no_error};

    if (errorNumber == filePaths.size())
    {
        errorCode = ErrorCode::error_all_files_not_read;
    }

    std::cout << errorNumber << filePaths.size();
    determineValidity("", errorCode, errorLevel, message, callingFunction);

    //Вернуть документы
    return {documents, errorCode};
}
