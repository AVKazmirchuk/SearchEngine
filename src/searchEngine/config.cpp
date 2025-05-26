//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"



void SearchEngine::ConfigSearchEngine::initialize()
{
    //Создать JSON-объект конфигурации
    configJSON = ReadWriteJSONFile::readJSONFile(configFilePath, configTemplate);
    requestsJSON = ReadWriteJSONFile::readJSONFile(requestsFilePath, requestsTemplate);
}