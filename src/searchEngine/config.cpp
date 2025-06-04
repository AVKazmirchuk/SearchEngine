//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"



void SearchEngine::ConfigSearchEngine::initialize()
{

    //Создать JSON-объект конфигурации
    configJSON = FileOperation::readJSONFile(configFilePath);

    FileOperation::checkJSON(configFilePath, configJSON, configTemplate);


    requestsJSON = FileOperation::readJSONFile(requestsFilePath);

    FileOperation::checkJSON(requestsFilePath, requestsJSON, requestsTemplate);
}