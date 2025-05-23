//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_CHECKFILE_H
#define SEARCH_ENGINE_CHECKFILE_H



#include <filesystem>
#include <fstream>

#include "nlohmann/json.hpp"

#include "checkFileException.h"
#include "general.h"
#include "logger.h"



/**
 * Класс реализует проверку файла и его содержимого (JSON-структуру)
 */
class CheckFile
{

public:

    CheckFile() = delete;

    //Проверить файл на существование
    static bool isFileExists(const std::string& filePath, const std::string& message)
    {
        if (!std::filesystem::exists(filePath))
        {
            Logger::error(message);

            return false;
        }

        return true;
    }

    //Проверить файл на существование
    static void isFileExists(const std::string& filePath, const std::string& message, const std::exception&)
    {
        if (!std::filesystem::exists(filePath))
        {
            Logger::fatal(message, CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath));
            throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath);
        }
    }

    //Проверить файл на открытие для чтения
    static bool isFileOpenRead(const std::ifstream& inFile, const std::string& filePath, const std::string& message)
    {
        isFileExists(filePath, message);

        if (!inFile.is_open())
        {
            Logger::error(message);

            return false;
        }

        return true;
    }

    //Проверить файл на открытие для чтения
    static void isFileOpenRead(const std::ifstream& inFile, const std::string& filePath, const std::string& message, const std::exception&)
    {
        isFileExists(filePath, message, std::runtime_error("e"));

        if (!inFile.is_open())
        {
            Logger::fatal(message, CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath));
            throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath);
        }
    }

    //Проверить файл на открытие для чтения
    static bool isFileOpenWrite(const std::ofstream& outFile, const std::string& filePath, const std::string& message)
    {
        isFileExists(filePath, message);

        if (!outFile.is_open())
        {
            Logger::error(message);

            return false;
        }

        return true;
    }

    //Проверить файл на открытие для чтения
    static void isFileOpenWrite(const std::ofstream& outFile, const std::string& filePath, const std::string& message, const std::exception&)
    {
        isFileExists(filePath, message, std::runtime_error("e"));

        if (!outFile.is_open())
        {
            Logger::fatal(message, CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_WRITE, filePath));
            throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_WRITE, filePath);
        }
    }

    /**
     * Проверить файл на целостность JSON-структуры
     * @param fileName Имя файла
     * @return Файл целостный(true)/не целостный(false)
     */
    static bool isJSONStructureValid(std::ifstream& inFile, const std::string& filePath, const std::string& message);

    /**
     * Проверить файл на целостность JSON-структуры
     * @param fileName Имя файла
     * @return Файл целостный(true)/не целостный(false)
     */
    static void isJSONStructureValid(std::ifstream& inFile, const std::string& filePath, const std::string& message, const std::exception&);

    /**
     * Проверить JSON-структуру файла на соответствие шаблону
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate, const std::string& filePath, const std::string& message);

    /**
     * Проверить JSON-структуру файла на соответствие шаблону
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static void isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate, const std::string& filePath, const std::string& message, const std::exception&);



private:

    /**
     * Проверить JSON-структуру файла на соответствие шаблону (реализация)
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static bool isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate);
};



#endif //SEARCH_ENGINE_CHECKFILE_H



//void checkFile(const std::string& filePath, const JSON &objectJSONTemplate)
//{
    //Проверить файл на существование
    //if (!std::filesystem::exists(filePath))
    //{
    //    Logger::fatal("void checkFile(const std::string& filePath, const JSON &objectJSONTemplate)",
    //                  CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath));
    //    throw CheckFileException(ErrorCode::ERROR_FILE_MISSING, filePath);
    //}

    //Проверить файл на открытие для чтения
    //if (!std::ifstream(filePath).is_open())
    //{
    //    Logger::fatal("void checkFile(const std::string& filePath, const JSON &objectJSONTemplate)",
    //                  CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath));
    //    throw CheckFileException(ErrorCode::ERROR_FILE_NOT_OPEN_READ, filePath);
    //}

    //Проверить файл на целостность JSON-структуры
    //if (!CheckFile::isJSONStructureValid(filePath))
    //{
    //    Logger::fatal("void checkFile(const std::string& filePath, const JSON &objectJSONTemplate)",
    //                  CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, filePath));
    //    throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED, filePath);
    //}

    //Проверить JSON-структуру файла на соответствие шаблону
    //if (!CheckFile::isJSONStructureMatch( ReadWriteJSONFile::readJSONFile(filePath), objectJSONTemplate))
    //{
    //    Logger::fatal("void checkFile(const std::string& filePath, const JSON &objectJSONTemplate)",
    //                  CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH, filePath));
    //    throw CheckFileException(ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH, filePath);
    //}
//}