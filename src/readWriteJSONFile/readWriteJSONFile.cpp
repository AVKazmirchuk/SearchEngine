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

    static void determineJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate, const std::string& filePath, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (!CheckFile::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH;

        determineDegreeOfValidity(errorCode, filePath, callingFunction);
    }

    static void determineReadJSONFile(std::ifstream& inFile, const std::string& filePath, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (!CheckFile::isFileExists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!CheckFile::isFileOpenRead(inFile)) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_READ;
        else if (!CheckFile::isJSONStructureValid(inFile)) errorCode = ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED;

        determineDegreeOfValidity(errorCode, filePath, callingFunction);
    }

    static void determineWriteJSONFile(std::ofstream& outFile, const std::string& filePath, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (!CheckFile::isFileExists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!CheckFile::isFileOpenWrite(outFile)) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_WRITE;

        determineDegreeOfValidity(errorCode, filePath, callingFunction);
    }

private:

    enum Level
    {
        debug,
        info,
        warning,
        error,
        fatal
    };

    static void determineDegreeOfValidity(ErrorCode errorCode, const std::string& filePath, const std::string& callingFunction)
    {
        if (static_cast<int>(errorCode) != 0)
        {
            auto it{std::find_if(actionLevel.begin(), actionLevel.end(),
                                 [&callingFunction](const std::pair<std::string, Level> &elem) {
                                     return elem.first == callingFunction;
                                 })};

            if (it != actionLevel.end())
            {
                switch (it->second)
                {
                    case fatal:
                        Logger::fatal(callingFunction, CheckFileException(errorCode, filePath));
                        throw CheckFileException(errorCode, filePath);
                    case error:
                        Logger::error(callingFunction);
                        return;
                    case warning:
                        Logger::warning(callingFunction);
                        return;
                    case info:
                        Logger::info(callingFunction);
                        return;
                    case debug:
                        Logger::debug(callingFunction);
                        return;
                }
            }
            else
            {
                Logger::error(callingFunction);
                return;
            }
        }
    }

    inline static std::list<std::pair<std::string, Level>> actionLevel{
            {"void SearchEngine::ConfigSearchEngine::initialize()", fatal}
    };
};


void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath, const int formatByWidth, const std::source_location &callingFunction)
{

    std::cout << "writeJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для записи
    std::ofstream outFile{filePath};

    //CheckFile::isFileOpenWrite(outFile, filePath, "void ReadWriteJSONFile::writeJSONFile(const JSON& objectJSON, const std::string& filePath)", std::runtime_error("e"));

    DispatcherOperationValidity::determineWriteJSONFile(outFile, filePath, callingFunction.function_name());

    //Записать JSON-объект в файл
    outFile << std::setw(formatByWidth) << objectJSON;
}

JSON ReadWriteJSONFile::readJSONFile(const std::string& filePath, const JSON &objectJSONTemplate, const std::source_location &callingFunction)
{

    std::cout << "readJSONFile: " << callingFunction.function_name() << std::endl;

    //Создать объект для чтения
    std::ifstream inFile(filePath);

    DispatcherOperationValidity::determineReadJSONFile(inFile, filePath, callingFunction.function_name());

    //Прочитать файл в JSON-объект
    JSON targetJSON = JSON::parse(inFile);

    DispatcherOperationValidity::determineJSONStructureMatch(targetJSON, objectJSONTemplate, filePath, callingFunction.function_name());

    //Вернуть JSON-объект
    return targetJSON;
}

