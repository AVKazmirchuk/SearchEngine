//
// Created by Alexander on 24.01.2026.
//

#ifndef KAV_LOGGER_TESTGENERAL_H
#define KAV_LOGGER_TESTGENERAL_H



#include "logger.h"



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
    static const std::string& messageForException();

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



//Получить путь текущего файла логирования
std::string getLastFilePath();

//Перевести отметку времени в строку
std::string timePointToString(const std::chrono::system_clock::time_point& now);

//Получить отметку времени
std::string  getTimePoint();

//Соответствует ли фактический уровень логирования ожидаемому
bool isMatchingErrorLevel(const std::string& timePoint, const std::string& strErrorLevel);

////Соответствует ли фактический уровень логирования ожидаемому для исключения
bool isMatchingErrorLevelForException(const std::string& timePoint, const std::string& message, const std::string& strErrorLevel);



#endif //KAV_LOGGER_TESTGENERAL_H
