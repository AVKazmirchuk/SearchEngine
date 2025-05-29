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

enum class ErrorLevel
{
    debug,
    info,
    warning,
    error,
    fatal
};

/**
 * Класс реализует проверку файла и его содержимого (JSON-структуру)
 */
class CheckFile
{

public:

    CheckFile() = delete;

    static void isReadJSONFile(std::ifstream& inFile, const std::string& filePath, ErrorLevel errorLevel)
    {
        ErrorCode errorCode{};

        if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!inFile.is_open()) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_READ;
        else if (!CheckFile::isJSONStructureValid(inFile)) errorCode = ErrorCode::ERROR_FILE_STRUCTURE_CORRUPTED;

        determineDegreeOfValidity(errorCode, filePath, errorLevel);
    }

    /**
     * Проверить файл на целостность JSON-структуры
     * @param fileName Имя файла
     * @return Файл целостный(true)/не целостный(false)
     */
    static bool isJSONStructureValid(std::ifstream& inFile);

    /**
     * Проверить JSON-структуру файла на соответствие шаблону
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);

private:



    static void determineDegreeOfValidity(ErrorCode errorCode, const std::string& filePath, ErrorLevel errorLevel)
    {
        if (static_cast<int>(errorCode) != 0)
        {



                switch (errorLevel)
                {
                    case ErrorLevel::fatal:
                        Logger::fatal(callingFunction, CheckFileException(errorCode, filePath));
                        throw CheckFileException(errorCode, filePath);
                    case ErrorLevel::error:
                        Logger::error(callingFunction);
                        return;
                    case ErrorLevel::warning:
                        Logger::warning(callingFunction);
                        return;
                    case ErrorLevel::info:
                        Logger::info(callingFunction);
                        return;
                    case ErrorLevel::debug:
                        Logger::debug(callingFunction);
                        return;
                }


            {
                Logger::error(callingFunction);
                return;
            }
        }
    }

    /**
     * Проверить JSON-структуру файла на соответствие шаблону (реализация)
     * @param objectJSON JSON-объект проверяемого
     * @param objectJSONTemplate JSON-объект шаблона
     * @return Файл соответствуе(true)/не соответствует(false)
     */
    static bool isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate);
};

using namespace std::string_literals;

class DispatcherOperationValidity
{

public:

    static void determineJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate, const std::string& filePath, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (!CheckFile::isJSONStructureMatch(objectJSON, objectJSONTemplate)) errorCode = ErrorCode::ERROR_FILE_STRUCTURE_NOT_MATCH;

        determineDegreeOfValidity(errorCode, filePath, callingFunction);
    }

    static void determineFilePathsArrayEmpty(const JSON &objectJSON, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (objectJSON.empty()) errorCode = ErrorCode::ERROR_FILE_PATHS_ARRAY_EMPTY;

        determineDegreeOfValidity(errorCode, "...", callingFunction);
    }

    static void determineRequestsArrayEmpty(const JSON &objectJSON, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (objectJSON.empty()) errorCode = ErrorCode::ERROR_REQUESTS_ARRAY_EMPTY;

        determineDegreeOfValidity(errorCode, "...", callingFunction);
    }

    static void determineReadFile(std::ifstream& inFile, const std::string& filePath, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!inFile.is_open()) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_READ;

        determineDegreeOfValidity(errorCode, filePath, callingFunction);
    }



    static void determineWriteJSONFile(std::ofstream& outFile, const std::string& filePath, const std::string& callingFunction)
    {
        ErrorCode errorCode{};

        if (!std::filesystem::exists(filePath)) errorCode = ErrorCode::ERROR_FILE_MISSING;
        else if (!outFile.is_open()) errorCode = ErrorCode::ERROR_FILE_NOT_OPEN_WRITE;

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
            {"void SearchEngine::ConfigSearchEngine::initialize()", fatal},
            {"void SearchEngine::writeAnswersToFile(const JSON&, const string&)", fatal},
            {"std::vector<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char> > > "s +
            "SearchEngine::readDocsFromFiles(const std::vector<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char> > >&)"s, fatal},
            {"void ConverterJSON::initialize()", fatal}
    };
};



#endif //SEARCH_ENGINE_CHECKFILE_H

