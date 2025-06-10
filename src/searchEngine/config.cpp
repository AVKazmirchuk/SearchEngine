//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"



void SearchEngine::ConfigSearchEngine::initialize()
{

    //Создать JSON-объект конфигурации
    //configJSON = OperationValidity::readJSONFile(configFilePath).value();
    if (auto tmp = OperationFileAndJSON::readJSONFile(configFilePath);!tmp.has_value())
    {
        DispatcherDetermineValidity::determineValidity(configFilePath, tmp.error());
    }
    else
    {
        configJSON = tmp.value();
    }

    OperationFileAndJSON::checkJSONStructureMatch(configFilePath, configJSON, configTemplate);


    requestsJSON = OperationFileAndJSON::readJSONFile(requestsFilePath).value();

    OperationFileAndJSON::checkJSONStructureMatch(requestsFilePath, requestsJSON, requestsTemplate);
}