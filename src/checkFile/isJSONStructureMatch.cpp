//
// Created by Alexander on 05.03.2025.
//



#include "checkFile.h"



bool CheckFile::isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate)
{
    auto elem = objectJSON.begin();

    for (const auto &elemTemplate: objectJSONTemplate.items()) {
        //Если в файле меньше полей чем в шаблоне или поля не равны (разные названия)
        if (elem == objectJSON.end() || elemTemplate.key() != elem.key()) return false;


        //Если значение поля - есть JSON-объект, тогда функция вызывает сома себя с текущими аргументами
        if (elemTemplate.value().is_object()) {
            isJSONStructureMatch(elem.value(), elemTemplate.value());
        }

        ++elem;
    }

    return true;
}