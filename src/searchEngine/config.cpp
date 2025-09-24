//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"
#include "DispatcherOperationValidity.h"


void SearchEngine::ConfigSearchEngine::initialize()
{
    //Создать JSON-объект конфигурации
    configJSON = DispatcherOperationValidity::readJSONFile(configFilePath).first;
    //Проверить JSON-структуру на соответствие шаблону
    DispatcherOperationValidity::checkJSONStructureMatch(configFilePath, configJSON, configTemplate);

    //Создать JSON-объект запросов
    requestsJSON = DispatcherOperationValidity::readJSONFile(requestsFilePath).first;
    //Проверить JSON-структуру на соответствие шаблону
    DispatcherOperationValidity::checkJSONStructureMatch(requestsFilePath, requestsJSON, requestsTemplate);
}