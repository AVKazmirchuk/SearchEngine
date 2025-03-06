//
// Created by Alexander on 27.01.2025.
//



#include "checkFile.h"



//Вспомогательная функция проверки файла на неповреждённость JSON-структуры
bool CheckFile::isJSONStructureValid(const std::string &fileName)
{
    std::ifstream inFile(configFilePath.string());

    try
    {
        inFile >> objectJSON;
    }
    catch (const nlohmann::detail::parse_error &e)
    {
        inFile.close();
        return false;
    }

    inFile.close();
    return true;
}

