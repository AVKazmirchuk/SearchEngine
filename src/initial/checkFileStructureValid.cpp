//
// Created by Alexander on 27.01.2025.
//



#include "initialize.h"



//Вспомогательная функция проверки файла на неповреждённость JSON-структуры
bool Initialize::checkFileStructureValid()
{
    std::ifstream inFile(filePath.string());

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

//Вспомогательные функции для функций проверки