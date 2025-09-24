//
// Created by Alexander on 07.03.2025.
//



#include "converterJSON.h"



void ConverterJSON::checkFilePath()
{
    //Проверить массив JSON-объекта путей файлов на пустоту
    DispatcherOperationValidity::checkFilePathsArray(configJSON[ConfigConverterJSON::filesStr]);
}

void ConverterJSON::checkRequests()
{
    //Проверить массив JSON-объекта запросов на пустоту
    DispatcherOperationValidity::checkRequestsArray(requestsJSON[ConfigConverterJSON::requestsStr]);
}