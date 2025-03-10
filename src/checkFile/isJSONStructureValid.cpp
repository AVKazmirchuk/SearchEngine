//
// Created by Alexander on 27.01.2025.
//



#include "checkFile.h"



bool CheckFile::isJSONStructureValid(const std::string &fileName)
{
    //Создать объект для проверки файла
    std::ifstream inFile(fileName);
    //Создать временный объект для поверки
    JSON tmpJSON;

    try
    {
        //Прочитать JSON-структуру
        inFile >> tmpJSON;
    }
    catch (const nlohmann::detail::parse_error &e)
    {
        inFile.close();
        //JSON-структура повреждена
        return false;
    }

    inFile.close();
    //JSON-структура целостна
    return true;
}

