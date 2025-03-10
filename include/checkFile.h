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
 * Класс реализует проверку файла и его содержимого (JSON-структуру)
 */
class CheckFile
{

public:

    CheckFile() = default;

    /**
     * Проверить файл на существование
     * @param fileName Имя файла
     * @return Файл существует(true)/не существует(false)
     */
    bool isExist(const std::string &fileName);

    /**
     * Проверить файл на пустоту
     * @param fileName Имя файла
     * @return Файл пустой(true)/не пустой(false)
     */
    bool isEmpty(const std::string &fileName);

    /**
     * Проверить файл на целостность JSON-структуры
     * @param fileName Имя файла
     * @return Файл целостный(true)/не целостный(false)
     */
    bool isJSONStructureValid(const std::string &fileName);

    /**
     * Проверить JSON-структуру файла на соответствие шаблону
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);

private:

    /**
     * Проверить JSON-структуру файла на соответствие шаблону (реализация)
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    bool isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate);
};



#endif //SEARCH_ENGINE_CHECKFILE_H
