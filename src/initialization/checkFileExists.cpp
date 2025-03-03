//
// Created by Alexander on 27.01.2025.
//



#include "Initialization.h"



//Вспомогательная функция проверки файла на существование
bool initialization::checkFileExists()
{
    return std::filesystem::exists(configFilePath);
}