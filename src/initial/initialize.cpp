//
// Created by Alexander on 28.01.2025.
//



#include "initialize.h"
#include "exceptions.h"


void Initialize::openFile()
{
    //Проверка файла на существование
    if (!checkFileExists()) throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath.string());

    //Проверка файла на неповреждённость JSON-структуры
    if (!checkFileStructureValid()) throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, filePath.string());

    if (!checkFileEmpty()) throw CheckFileException(ErrorCode::ERROR_FILE_EMPTY, filePath.string());
}

std::string Initialize::about()
{
    return to_string(objectJSON["config"]["name"]) + ", v." + to_string(objectJSON["config"]["version"]);
}