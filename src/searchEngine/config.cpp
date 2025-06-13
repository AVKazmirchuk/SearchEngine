//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"
#include "dispatcherDetermineValidity.h"


void SearchEngine::ConfigSearchEngine::initialize()
{

    //Создать JSON-объект конфигурации
    configJSON = DispatcherDetermineValidity::readJSONFile(configFilePath).first;

    DispatcherDetermineValidity::checkJSONStructureMatch(configFilePath, configJSON, configTemplate);


    requestsJSON = DispatcherDetermineValidity::readJSONFile(requestsFilePath).first;

    DispatcherDetermineValidity::checkJSONStructureMatch(requestsFilePath, requestsJSON, requestsTemplate);
}