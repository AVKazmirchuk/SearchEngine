//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"



void SearchEngine::ConfigSearchEngine::initialize()
{

    //Создать JSON-объект конфигурации
    configJSON = OperationValidity::readJSONFile(configFilePath);

    OperationValidity::checkJSON(configFilePath, configJSON, configTemplate);


    requestsJSON = OperationValidity::readJSONFile(requestsFilePath);

    OperationValidity::checkJSON(requestsFilePath, requestsJSON, requestsTemplate);
}