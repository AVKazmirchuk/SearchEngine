//
// Created by Alexander on 07.05.2025.
//

#ifndef SEARCH_ENGINE_OPERATIONFILEANDJSON_H
#define SEARCH_ENGINE_READWRITEJSONFILE_H



#include "nlohmann/json.hpp"

#include "general.h"



/**
 * Класс реализует чтение и запись JSON-файлов
 */
class ReadWriteJSONFile
{

public:

    ReadWriteJSONFile() = default;

    /**
     * Прочитать JSON-файл
     * @param filePath Путь JSON-файла
     * @return JSON-файл
     */
    static JSON readJSONFile(const std::string& filePath);

    /**
     * Записать JSON-файл
     * @param objectJSON JSON-объект
     * @param filePath Путь JSON-файла
     */
    static void writeJSONFile(const JSON& objectJSON, const std::string& filePath);

};



#endif //SEARCH_ENGINE_OPERATIONFILEANDJSON_H
