//
// Created by Alexander on 28.01.2025.
//



#include "checkFile.h"
#include "exceptions.h"


void CheckFile::checkFile(const std::string &fileName)
{




    /*
    //Проверить файл на существование
    if (!checkFileExists(fileName)) throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, configFilePath.string());

    //Проверка файла на неповреждённость JSON-структуры
    if (!checkJSONStructureValid()) throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, configFilePath.string());

    if (!checkFileEmpty()) throw CheckFileException(ErrorCode::ERROR_FILE_EMPTY, configFilePath.string());
    */
}

std::string CheckFile::about()
{
    return to_string(objectJSON[constants::configStr][constants::nameStr]) + ", v." +
                     to_string(objectJSON[constants::configStr][constants::versionStr]);
}