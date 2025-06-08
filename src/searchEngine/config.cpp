//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"



void SearchEngine::ConfigSearchEngine::initialize()
{

    //Создать JSON-объект конфигурации
    //configJSON = OperationValidity::readJSONFile(configFilePath).value();
    if (auto tmp = OperationValidity::readJSONFile(configFilePath);!tmp.has_value())
    {
        DispatcherOperationValidity::determineDegreeOfValidity(configFilePath, tmp.error());
    }
    else
    {
        configJSON = tmp.value();
    }

    OperationValidity::checkJSON(configFilePath, configJSON, configTemplate);


    requestsJSON = OperationValidity::readJSONFile(requestsFilePath).value();

    OperationValidity::checkJSON(requestsFilePath, requestsJSON, requestsTemplate);
}