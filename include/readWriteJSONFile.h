//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_READWRITEJSONFILE_H
#define SEARCH_ENGINE_READWRITEJSONFILE_H



#include <fstream>

#include "nlohmann/json.hpp"

#include "checkFile.h"
#include "general.h"
#include <source_location>
#include "boost/current_function.hpp"


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
    static JSON readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate, ErrorLevel errorLevel);

    /**
     * Записать JSON-файл
     * @param objectJSON JSON-объект
     * @param filePath Путь JSON-файла
     */
    static void writeJSONFile(const JSON& objectJSON, const std::string& filePath, const int formatByWidth = 2,
                              const std::source_location &callingFunction = std::source_location::current());

};

#endif //SEARCH_ENGINE_READWRITEJSONFILE_H
