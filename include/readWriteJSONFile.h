//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_READWRITEJSONFILE_H
#define SEARCH_ENGINE_READWRITEJSONFILE_H



#include <fstream>

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
    static JSON readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate, std::string str = __builtin_FUNCTION());

    /**
     * Записать JSON-файл
     * @param objectJSON JSON-объект
     * @param filePath Путь JSON-файла
     */
    static void writeJSONFile(const JSON& objectJSON, const std::string& filePath, const int formatByWidth = 2);

};

#endif //SEARCH_ENGINE_READWRITEJSONFILE_H
