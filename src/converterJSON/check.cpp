//
// Created by Alexander on 07.03.2025.
//



#include "converterJSON.h"



void ConverterJSON::checkFilePath()
{
    //Проверить массив JSON-объекта путей файлов на пустоту
    DispatcherOperations::checkFilePathsArray(configJSON[FileFieldNames::filesStr]);
}

void ConverterJSON::checkRequests()
{
    //Проверить массив JSON-объекта запросов на пустоту
    DispatcherOperations::checkRequestsArray(requestsJSON[FileFieldNames::requestsStr]);
}