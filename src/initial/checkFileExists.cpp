//
// Created by Alexander on 27.01.2025.
//



#include "initialize.h"



//Вспомогательная функция проверки файла на существование
bool Initialize::checkFileExists()
{
    return std::filesystem::exists(filePath);
}