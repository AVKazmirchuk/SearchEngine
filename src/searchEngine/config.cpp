//
// Created by Alexander on 25.05.2025.
//

#include "searchEngine.h"
#include "dispatcherDetermineValidity.h"


void SearchEngine::ConfigSearchEngine::initialize()
{
    //Создать JSON-объект конфигурации
    configJSON = DispatcherDetermineValidity::readJSONFile(configFilePath).first;
    //Проверить JSON-структуру на соответствие шаблону
    DispatcherDetermineValidity::checkJSONStructureMatch(configFilePath, configJSON, configTemplate);

    //Создать JSON-объект запросов
    requestsJSON = DispatcherDetermineValidity::readJSONFile(requestsFilePath).first;
    //Проверить JSON-структуру на соответствие шаблону
    DispatcherDetermineValidity::checkJSONStructureMatch(requestsFilePath, requestsJSON, requestsTemplate);
}