//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"



void SearchEngine::ConfigSearchEngine::initialize()
{

    //Создать JSON-объект конфигурации
    configJSON = ReadWriteJSONFile::readJSONFile(configFilePath);

    ReadWriteJSONFile::checkJSON(configFilePath, configJSON, configTemplate);


    requestsJSON = ReadWriteJSONFile::readJSONFile(requestsFilePath);

    ReadWriteJSONFile::checkJSON(requestsFilePath, requestsJSON, requestsTemplate);
}