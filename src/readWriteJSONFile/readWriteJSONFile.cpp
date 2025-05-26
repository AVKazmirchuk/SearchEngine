//
// Created by Alexander on 31.03.2025.
//

#include <source_location>
#include <algorithm>
#include <list>

#include "checkFile.h"
#include "readWriteJSONFile.h"
#include "logger.h"
#include "boost/current_function.hpp"
#include "checkFileException.h"



class DispatcherOperationValidity
{

public:

    static void checkFileOperations(std::ifstream& inFile, const std::string& filePath, const std::string& callingFunction)
    {
        ErrorCode error{};

        if (!CheckFile::isFileExists(filePath)) error = ErrorCode::ERROR_FILE_MISSING;
        else if (!CheckFile::isFileOpenRead(inFile)) error = ErrorCode::ERROR_FILE_NOT_OPEN_READ;
        else if (!CheckFile::isJSONStructureValid(inFile)) error = ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED;

        if (static_cast<int>(error) != 0)
        {
            auto it{std::find_if(actionLevel.begin(), actionLevel.end(),
                                 [&callingFunction](const std::pair<std::string, std::string> &elem) {
                                     return elem.first == callingFunction;
                                 })};

            if (it != actionLevel.end())
            {
                if (it->second == "fatal")
                {
                    Logger::fatal(callingFunction, CheckFileException(error, filePath));
                    throw CheckFileException(error, filePath);
                }
                else if (it->second == "error")
                {
                    Logger::error(callingFunction);
                }
                else if (it->second == "warning")
                {
                    Logger::warning(callingFunction);
                }
                else if (it->second == "info")
                {
                    Logger::info(callingFunction);
                }

            }
        }




    }

private:

    inline static std::list<std::pair<std::string, std::string>> actionLevel{
            {"void SearchEngine::ConfigSearchEngine::initialize()", "fatal"}
    };
};


void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath, const int formatByWidth)
{
    //Создать объект для записи
    std::ofstream outFile{filePath};

    CheckFile::isFileOpenWrite(outFile, filePath, "void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", std::runtime_error("e"));

    //Записать JSON-объект в файл
    outFile << std::setw(formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate, const std::source_location &callingFunction)
{

    std::cout << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    DispatcherOperationValidity::checkFileOperations(inFile, filePath, callingFunction);

    //CheckFile::isJSONStructureValid(inFile, filePath, "JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath)", std::runtime_error("e"));

    //Прочитать файл в JSON-объект
    JSON targetJSON = JSON::parse(inFile);

    CheckFile::isJSONStructureMatch(targetJSON, objectJSONTemplate, filePath,
                                    "JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate)",
                                    std::runtime_error("e"));

    //Вернуть JSON-объект
    return targetJSON;
}

