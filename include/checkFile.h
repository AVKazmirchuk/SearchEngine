//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_CHECKFILE_H
#define SEARCH_ENGINE_CHECKFILE_H



#include <filesystem>
#include <fstream>

#include "nlohmann/json.hpp"

#include "exceptions.h"
#include "general.h"


/**
 * Класс реализует проверку файла и его содержимого
 */
class CheckFile
{

public:

    CheckFile() = default;

    /**
     * Проверить файл на существование
     * @param fileName Имя файла
     * @return
     */
    bool isExist(const std::string &fileName);

    /**
     * Проверить файл на пустоту
     * @param fileName Имя файла
     * @return
     */
    bool isEmpty(const std::string &fileName);

    /**
     * Проверить файл на целостность JSON-структуры
     * @param fileName Имя файла
     * @return
     */
    bool isJSONStructureValid(const std::string &fileName);

    /**
     * Проверить JSON-структуру файла на соответствие шаблону
     * @param objectJSONTemplate
     * @param objectJSON
     * @return
     */
    bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);

private:

    bool isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate);
};



#endif //SEARCH_ENGINE_CHECKFILE_H
