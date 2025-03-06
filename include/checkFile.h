//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_CHECKFILE_H
#define SEARCH_ENGINE_CHECKFILE_H



#include <filesystem>
#include <fstream>

#include "nlohmann/json.hpp"

#include "general.h"



class CheckFile
{

public:

    CheckFile() = default;


    void checkFile(const std::string& fileName);

    std::string about();

private:

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
    bool isJSONStructureMatch(const JSON &objectJSONTemplate, const JSON &objectJSON);

};



#endif //SEARCH_ENGINE_CHECKFILE_H
