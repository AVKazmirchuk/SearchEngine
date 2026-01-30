//
// Created by Alexander on 27.03.2025.
//

#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H



#include "nlohmann/json.hpp"

#include "constants.h"
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
     * Прочитать путь файла конфигурации missing. Файл отсутствует
     * @return Ссылка на переменную
     */
    static const std::string& configFilePath_missing();

    /**
     * Прочитать путь файла конфигурации. Список путей файлов документов пуст
     * @return Ссылка на переменную
     */
    static const std::string& configFilePath_filesEmpty();

    /**
     * Прочитать путь файла конфигурации. File003 отсутствует
     * @return Ссылка на переменную
     */
    static const std::string& configFilePath_file003_missing();

    /**
     * Прочитать путь файла запросов
     * @return Ссылка на переменную
     */
    static const std::string& requestsFilePath();

    /**
     * Прочитать путь файла запросов missing. Файл отсутствует
     * @return Ссылка на переменную
     */
    static const std::string& requestsFilePath_missing();

    /**
     * Прочитать путь файла запросов. Список запросов пуст
     * @return Ссылка на переменную
     */
    static const std::string& requestsFilePath_requestsEmpty();

    /**
     * Прочитать путь файла ответов
     * @return Ссылка на переменную
     */
    static const std::string& answersFilePath();

    /**
     * Прочитать путь файла теста чтения JSON-файла
     * @return Ссылка на переменную
     */
    static const std::string& readJSONFile();

    /**
     * Прочитать путь файла теста чтения JSON-файла. Файл отсутствует
     * @return Ссылка на переменную
     */
    static const std::string& readMissingJSONFile();

    /**
     * Прочитать путь файла теста чтения текстового файла
     * @return Ссылка на переменную
     */
    static const std::string& readTextFile();

    /**
     * Прочитать путь файла теста чтения текстового файла. Файл отсутствует
     * @return Ссылка на переменную
     */
    static const std::string& readMissingTextFile();

    /**
     * Прочитать JSON-объект массива запросов
     * @return Ссылка на переменную
     */
    static const std::string& checkRequestsArray();

    /**
     * Прочитать путь файла ответов
     * @return Ссылка на переменную
     */
    static const std::string& answersFilePath_empty();

    /**
     * Прочитать/записать признак формирования базы документов или путей файлов документов
     * @return Ссылка на переменную
     */
    static const std::string& documentsBaseOrPathsBase();

    /**
     * Прочитать/записать признак формирования базы документов или путей файлов документов. Пути файлов документов
     * @return Ссылка на переменную
     */
    static const std::string &documentsBaseOrPathsBase_no();

    /**
     * Прочитать/записать путь файла конфигурации логирования
     * @return Ссылка на переменную
     */
    static const std::string& configLoggerFilePath();

    /**
     * Прочитать/записать путь файла конфигурации очереди сообщений
     * @return Ссылка на переменную
     */
    static const std::string& configWriterMessageFilePath();

    /**
     * Прочитать имя папки логов
     * @return Имя папки логов
     */
    static const std::string& logsFolderName();


    /**
     * Прочитать имя JSON-файла
     * @return
     */
    static const std::string& jsonFileName();

    /**
     * Прочитать тестовое сообщение
     * @return Тестовое сообщение
     */
    static const std::string& dispatcherOperations_writeJSONFile_info();

    /**
     * Прочитать уровень логирования debug
     * @return
     */
    static const std::string& errorLevel_debug();

    /**
     * Прочитать уровень логирования info
     * @return
     */
    static const std::string& errorLevel_info();

    /**
     * Прочитать уровень логирования warning
     * @return
     */
    static const std::string& errorLevel_warning();

    /**
     * Прочитать уровень логирования error
     * @return
     */
    static const std::string& errorLevel_error();

    /**
     * Прочитать уровень логирования fatal
     * @return
     */
    static const std::string& errorLevel_fatal();

    /**
     * Прочитать формат даты и времени
     * @return
     */
    static const std::string& dateTimeFormat();

    /**
     * Прочитать/записать признак логирования событий в консоль
     * @return Ссылка на переменную
     */
    static const std::string& launchConsole_yes();

    /**
     * Прочитать/записать признак логирования событий в консоль
     * @return Ссылка на переменную
     */
    static const std::string& launchConsole_no();

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
     * Прочитать желаемое количество потоков
     * @return Ссылка на переменную
     */
    static unsigned int desiredNumberOfThreads();

    /**
     * Прочитать желаемое количество потоков. Один поток
     * @return Ссылка на переменную
     */
    static unsigned int desiredNumberOfThreads_1();

    /**
     * Прочитать желаемое количество потоков. Три потока
     * @return Ссылка на переменную
     */
    static unsigned int desiredNumberOfThreads_3();

    /**
     * Прочитать максимальное количество непрочитанных файлов
     * @return Ссылка на переменную
     */
    static const std::size_t& maximumAllowableErrorsNumber_0();

    /**
     * Прочитать максимальное количество непрочитанных файлов. Один ошибочный файл
     * @return Ссылка на переменную
     */
    static const std::size_t& maximumAllowableErrorsNumber_1();

    /**
     * Прочитать максимальное количество непрочитанных файлов. Два ошибочных файла
     * @return Ссылка на переменную
     */
    static const std::size_t& maximumAllowableErrorsNumber_2();

    /**
     * Прочитать максимальное количество непрочитанных файлов. Два ошибочных файла
     * @return Ссылка на переменную
     */
    static const std::size_t& packageID_0();

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
     * Получить ссылку на базу документов. Два документа отсутствуют
     * @return Ссылка на базу документов
     */
    static const std::vector<std::string> &documents_file001_002_missing();

    /**
     * Получить ссылку на пути файлов документов
     * @return Ссылка на пути файлов документов
     */
    static const std::vector<std::string> &paths();

    /**
     * Получить ссылку на пути файлов документов. File001-002 отсутствуют
     * @return Ссылка на пути файлов документов
     */
    static const std::vector<std::string> &paths_file001_002_missing();

    /**
     * Получить ссылку на пути файлов документов. Все файлы отсутствуют
     * @return Ссылка на пути файлов документов
     */
    static const std::vector<std::string> &paths_files_all_missing();

    /**
     * Получить ссылку на пути файлов документов. File003 отсутствует
     * @return Ссылка на пути файлов документов
     */
    static const std::vector<std::string> &paths_file003_missing();

    /**
     * Получить ссылку на базу инвертированного индекса
     * @return Ссылка на базу инвертированного индекса
     */
    static const std::map<std::string, std::vector<Entry>> &invertedIndex();

    /**
     * Получить ссылку на базу инвертированного индекса. File003 отсутствует
     * @return Ссылка на базу инвертированного индекса
     */
    static const std::map<std::string, std::vector<Entry>> &invertedIndex_file003_missing();

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
     * Получить ссылку на базу релевантности ответов. File003 отсутствует
     * @return Ссылка на базу релевантности ответов
     */
    const std::vector<std::vector<RelativeIndex>> &relativeIndex_file003_missing();

    /**
     * Получить ссылку на базу релевантности ответов. Количество знаков после запятой: 3
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
     * Получить ссылку на JSON-объект конфигурации несоответствующий шаблону
     * @return Ссылка на JSON-объект конфигурации
     */
    static const JSON &configNotMatchJSON();

    /**
     * Получить ссылку на JSON-объект конфигурации пустого массива путей файлов
     * @return Ссылка на JSON-объект конфигурации
     */
    static const JSON &configEmptyJSON();

    /**
    * Получить ссылку на JSON-объект конфигурации полного массива путей файлов
    * @return Ссылка на JSON-объект конфигурации
    */
    static const JSON &configFullJSON();

    /**
     * Получить ссылку на JSON-объект запросов
     * @return Ссылка на JSON-объект запросов
     */
    static const JSON &requestsJSON();

    /**
     * Получить ссылку на JSON-объект пустого массива запросов
     * @return Ссылка на JSON-объект запросов
     */
    static const JSON &requestsEmptyJSON();

    /**
     * Получить ссылку на JSON-объект полного массива запросов
     * @return Ссылка на JSON-объект запросов
     */
    static const JSON &requestsFullJSON();

    /**
     * Получить ссылку на JSON-объект
     * @return Ссылка на JSON-объект
     */
    static const JSON &jsonTest();

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

    /**
     * Получить ссылку на JSON-объект ответов
     * @return Ссылка на JSON-объект ответов
     */
    static const JSON &answersJSON_file003_missing();

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
                        {"DispatcherOperations::readMultipleTextFiles",                 ErrorLevel::error},
                        {"testReadMultipleTextFiles",                                   ErrorLevel::fatal},
                        {"testReadMultipleTextFilesSequentially",                       ErrorLevel::fatal},
                        {"InvertedIndex::readDocument",                                 ErrorLevel::fatal},
                        {"SearchEngine::readDocsFromFiles",                             ErrorLevel::fatal},
                        {"SearchEngine::readDocsFromFilesRef",                          ErrorLevel::fatal},
                        {"SearchEngine::writeAnswersToFile",                            ErrorLevel::fatal}
                };

        return varMatchingFunctionNameAndErrorLevel;
    }

};//MatchingFunctionNameAndErrorLevel



//Получить путь текущего файла логирования
std::string getLastFilePath();

//Перевести отметку времени в строку
std::string timePointToString(const std::chrono::system_clock::time_point& now);

//Получить отметку времени
std::string  getTimePoint();

//Соответствует ли фактический уровень логирования ожидаемому
bool isMatchingErrorLevel(const std::string& timePoint, const std::string& strErrorLevel);

//Соответствует ли фактический уровень логирования ожидаемому для каждого файла
bool isMatchingErrorLevelForEachFile(const std::string& timePoint, const std::string& strErrorLevel, std::size_t maximumAllowableErrorsNumber);

#endif //SEARCH_ENGINE_TESTGENERAL_H
