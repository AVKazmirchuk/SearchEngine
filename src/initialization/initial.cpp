//
// Created by Alexander on 28.01.2025.
//



#include "Initialization.h"
#include "exceptions.h"


void initialization::openFile()
{
    //Проверка файла на существование
    if (!checkFileExists()) throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, configFilePath.string());

    //Проверка файла на неповреждённость JSON-структуры
    if (!checkJSONStructureValid()) throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, configFilePath.string());

    if (!checkFileEmpty()) throw CheckFileException(ErrorCode::ERROR_FILE_EMPTY, configFilePath.string());
}

std::string initialization::about()
{
    return to_string(objectJSON[constants::configStr][constants::nameStr]) + ", v." +
                     to_string(objectJSON[constants::configStr][constants::versionStr]);
}