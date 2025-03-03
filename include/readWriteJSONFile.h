//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_READWRITEJSONFILE_H
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
    JSON readJSONFile(const std::string& filePath);

    /**
     * Записать JSON-файл
     * @param objectJSON JSON-файл
     * @param filePath Путь JSON-файла
     * @param formatByWidth Ширина вывода
     */
    void writeJSONFile(const JSON& objectJSON, const std::string& filePath);

};

#endif //SEARCH_ENGINE_READWRITEJSONFILE_H
