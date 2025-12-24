//
// Created by Alexander on 31.03.2025.
//



#include "converterJSON.h"
#include <iostream>



void ConverterJSON::ConfigConverterJSON::initialize()
{
    //Создать JSON-объект конфигурации
    configJSON = DispatcherOperations::readJSONFile(configFilePath).first;
    //Проверить JSON-структуру на соответствие шаблону
    DispatcherOperations::checkJSONStructureMatch(configFilePath, configJSON, configTemplate);

    //Создать JSON-объект запросов
    requestsJSON = DispatcherOperations::readJSONFile(requestsFilePath).first;
    //Проверить JSON-структуру на соответствие шаблону
    DispatcherOperations::checkJSONStructureMatch(requestsFilePath, requestsJSON, requestsTemplate);
}

void ConverterJSON::initialize()
{
    //Проверить пути файлов документов (существование)
    checkFilePath();
    //Проверить запросы (существование)
    checkRequests();

    maxResponses = configJSON[FileFieldNames::configStr()][FileFieldNames::max_responsesStr()];

}

std::string ConverterJSON::about()
{
    //Вернуть строку о программе (название, версия)
    return to_string(configJSON[FileFieldNames::configStr()][FileFieldNames::nameStr()]) + ", v." +
           to_string(configJSON[FileFieldNames::configStr()][FileFieldNames::versionStr()]);
}

JSON& ConverterJSON::getAnswersJSON()
{
    return answersJSON;
}

std::vector<std::string> ConverterJSON::getFilePaths()
{
    //Определить список путей файлов документов
    std::vector<std::string> filePaths(configJSON[FileFieldNames::filesStr()]);

    return filePaths;
}

std::vector<std::string> ConverterJSON::getRequests()
{
    std::vector<std::string> requests;

    //Каждый запрос в JSON-объекте
    for (auto& elem : static_cast<std::vector<std::string>>(requestsJSON[FileFieldNames::requestsStr()]))
    {
        //Добавить в контейнер
        requests.push_back(elem);
    }

    return requests;
}