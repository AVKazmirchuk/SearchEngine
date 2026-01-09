//
// Created by Alexander on 27.03.2025.
//

#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H



#include "nlohmann/json.hpp"

#include "dispatcherOperations.h"
#include "entry.h"
#include "relativeIndex.h"
#include "types.h"



namespace testConstants
{
    extern const unsigned int precision;

    extern const unsigned int maxResponses;
}

/**
 * Класс хранения переменных аргументов программы
 */
class ProgramArguments
{

public:

    ProgramArguments() = delete;

    /**
     * Прочитать путь файла конфигурации
     * @return Ссылка на переменную
     */
    static const std::string& configFilePath();

    /**
     * Прочитать путь файла конфигурации 2. Изменено максимальное количество ответов
     * @return Ссылка на переменную
     */
    static const std::string& configFilePath_2();

    /**
     * Прочитать путь файла запросов
     * @return Ссылка на переменную
     */
    static const std::string& requestsFilePath();

    /**
     * Прочитать/записать путь файла ответов
     * @return Ссылка на переменную
     */
    static const std::string& answersFilePath();

    /**
     * Прочитать/записать признак формирования базы документов или путей файлов документов
     * @return Ссылка на переменную
     */
    static const std::string& documentsBaseOrPathsBase();

    /**
     * Прочитать/записать путь файла конфигурации логирования
     * @return Ссылка на переменную
     */
    static const std::string& configLoggerFilePath();

    /**
     * Прочитать/записать путь файла конфигурации очереди сообщений
     * @return Ссылка на переменную
     */
    static std::string& configWriterMessageFilePath();

    /**
     * Прочитать/записать признак логирования событий в консоль
     * @return Ссылка на переменную
     */
    static const std::string& launchConsole();

    /**
     * Прочитать количество знаков после запятой
     * @return Ссылка на переменную
     */
    static const unsigned int& precision();

    /**
     * Прочитать количество знаков после запятой
     * @return Ссылка на переменную
     */
    static const unsigned int& precision_3();

    /**
     * Прочитать/записать ширину вывода
     * @return Ссылка на переменную
     */
    static const int& formatByWidth();

    /**
     * Прочитать/записать желаемое количество потоков
     * @return Ссылка на переменную
     */
    static const unsigned int& desiredNumberOfThreads();

    /**
     * Прочитать/записать максимальное количество непрочитанных файлов
     * @return Ссылка на переменную
     */
    static const std::size_t& maximumAllowableErrorsNumber();

    /**
     * Прочитать максимальное количество ответов
     * @return Максимальное количество ответов
     */
    static unsigned int maxResponses();

};//Класс хранения переменных аргументов программы

/**
 * Класс хранения баз документов, инвертированного индекса, запросов, релевантности ответов
 */
class Bases
{

public:

    Bases() = delete;

    /**
     * Получить ссылку на базу документов
     * @return Ссылка на базу документов
     */
    static const std::vector<std::string> &documents();

    /**
     * Получить ссылку на базу инвертированного индекса
     * @return Ссылка на базу инвертированного индекса
     */
    static const std::map<std::string, std::vector<Entry>> &invertedIndex();

    /**
     * Получить ссылку на пути файлов документов
     * @return Ссылка на пути файлов документов
     */
    static const std::vector<std::string> &filePaths();

    /**
     * Получить ссылку на базу запросов
     * @return Ссылка на базу запросов
     */
    static const std::vector<std::string> &requests();

    /**
     * Получить информацию о программе
     * @return Информация о программе
     */
    static const std::string &about();

    /**
     * Получить ссылку на базу релевантности ответов
     * @return Ссылка на базу релевантности ответов
     */
    static const std::vector<std::vector<RelativeIndex>> &relativeIndex();

    /**
     * Получить ссылку на базу релевантности ответов
     * @return Ссылка на базу релевантности ответов
     */
    static const std::vector<std::vector<RelativeIndex>> &relativeIndex_3();

    /**
     * Получить ссылку на базу релевантности ответов другого типа
     * @return Ссылка на базу релевантности ответов другого типа
     */
    static const std::vector<std::vector<std::pair<std::uint64_t, float>>> &exportRelativeIndex();

    /**
     * Получить ссылку на JSON-объект конфигурации
     * @return Ссылка на JSON-объект конфигурации
     */
    static const JSON &configJSON();

    /**
     * Получить ссылку на JSON-объект запросов
     * @return Ссылка на JSON-объект запросов
     */
    static const JSON &requestsJSON();

    /**
     * Получить ссылку на JSON-объект ответов
     * @return Ссылка на JSON-объект ответов
     */
    static const JSON &answersJSON();

    /**
     * Получить ссылку на JSON-объект ответов
     * @return Ссылка на JSON-объект ответов
     */
    static const JSON &answersJSON_2();

    /**
     * Получить ссылку на JSON-объект ответов
     * @return Ссылка на JSON-объект ответов
     */
    static const JSON &answersJSON_3();

};//Bases

/**
 * Класс хранения контейнера соответствия имени вызывающей функции и уровня логирования.
 * Означает, что при вызове функций этого класса, уровни логирования прямо указываться не будут
 */
class MatchingFunctionNameAndErrorLevel
{

public:

    MatchingFunctionNameAndErrorLevel() = delete;

    /**
     * Получить ссылку на контейнер соответствия имени вызывающей функции и уровня логирования
     * @return Ссылка на контейнер
     */
    static const std::map<std::string, ErrorLevel> &matchingFunctionNameAndErrorLevel()
    {
        static const std::map<std::string, ErrorLevel> varMatchingFunctionNameAndErrorLevel
                {
                        {"ConverterJSON::ConfigConverterJSON::initialize",              ErrorLevel::fatal},
                        {"ConverterJSON::checkFilePath",                                ErrorLevel::fatal},
                        {"ConverterJSON::checkRequests",                                ErrorLevel::fatal},
                        {"DispatcherOperations::readMultipleTextFilesSequentially",     ErrorLevel::error},
                        {"InvertedIndex::readDocument",                                 ErrorLevel::fatal},
                        {"SearchEngine::readDocsFromFiles",                             ErrorLevel::fatal},
                        {"SearchEngine::readDocsFromFilesRef",                          ErrorLevel::fatal},
                        {"SearchEngine::writeAnswersToFile",                            ErrorLevel::fatal}
                };

        return varMatchingFunctionNameAndErrorLevel;
    }

};//MatchingFunctionNameAndErrorLevel

#endif //SEARCH_ENGINE_TESTGENERAL_H
