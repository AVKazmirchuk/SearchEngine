//
// Created by Alexander on 26.03.2025.
//



#include "checkFile.h"
#include "general.h"
#include "readWriteJSONFile.h"



void checkFile(const std::string& filePath, const JSON &objectJSONTemplate)
{
    //Проверить файл на существование
    if (!std::filesystem::exists(filePath))
    {
        throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath);
    }

    //Проверить файл на целостность JSON-структуры
    if (!CheckFile().isJSONStructureValid(filePath))
    {
        throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, filePath);
    }

    //Проверить JSON-структуру файла на соответствие шаблону
    if (!CheckFile().isJSONStructureMatch( ReadWriteJSONFile().readJSONFile(filePath), objectJSONTemplate))
    {
        throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH, filePath);
    }
}