//
// Created by Alexander on 24.01.2026.
//

#ifndef KAV_LOGGER_TESTGENERAL_H
#define KAV_LOGGER_TESTGENERAL_H



#include "kav/operationFileAndJSON.h"
#include "logger.h"

#include "monitor.h"
#include "monitorReceiver.h"


//Указатель для доступа к объекту из тестов
inline kav::LoggerMonitor *loggerMonitorExtern;

//Указатель для доступа к объекту из тестов
inline std::future<void> *futureRun;

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
     * Прочитать путь файла конфигурации логирования. Время использования файла 1 секунда
     * @return Ссылка на переменную
     */
    static const std::string& configLoggerFilePath_usage_1sec();

    /**
     * Прочитать путь файла конфигурации логирования. Время использования файла 3 секунды
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_usage_3sec();

    /**
     * Прочитать путь файла конфигурации логирования. Время хранения файла 3 секунды
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_storage_3sec();

    /**
     * Прочитать путь файла конфигурации логирования. Время хранения файла 3 секунды
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_storageTwoFile_3sec();

    /**
     * Прочитать путь файла конфигурации логирования. Время использования файла 6 секунд в минутах
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_usage_6sec_in_minutes();

    /**
     * Прочитать путь файла конфигурации логирования. Время хранения файла 6 секунд в минутах
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_storage_6sec_in_minutes();

    /**
     * Прочитать путь файла конфигурации логирования. Время использования файла 6 секунд в часах
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_usage_6sec_in_hours();

    /**
     * Прочитать путь файла конфигурации логирования. Время хранения файла 6 секунд в часах
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_storage_6sec_in_hours();

    /**
     * Прочитать путь файла конфигурации логирования. Время использования файла 6 секунд в днях
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_usage_6sec_in_days();

    /**
     * Прочитать путь файла конфигурации логирования. Время хранения файла 6 секунд в днях
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_storage_6sec_in_days();

    /**
     * Прочитать путь файла конфигурации логирования. Время использования файла 6 секунд в неделях
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_usage_6sec_in_weeks();

    /**
     * Прочитать путь файла конфигурации логирования. Время хранения файла 6 секунд в неделях
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_storage_6sec_in_weeks();

    /**
     * Прочитать путь файла конфигурации логирования. Размер файла 100 байт
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_size_200_bytes();

    /**
     * Прочитать путь файла конфигурации логирования. Файл отсутствует
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_missing();

    /**
     * Прочитать путь файла конфигурации логирования. Файл не соответствует шаблону
     * @return Путь файла
     */
    static const std::string& configLoggerFilePath_notMatch();

    /**
     * Прочитать/записать путь файла конфигурации очереди сообщений
     * @return Ссылка на переменную
     */
    static const std::string& configWriterMessageFilePath();

    /**
     * Прочитать/записать путь файла конфигурации очереди сообщений. Для тестирования логгера
     * @return Ссылка на переменную
     */
    static const std::string& configWriterMessageFilePath_loggerTest();

    /**
     * Прочитать/записать путь файла конфигурации очереди сообщений. Файл отсутствует
     * @return Ссылка на переменную
     */
    static const std::string& configWriterMessageFilePath_missing();

    /**
     * Прочитать/записать путь файла конфигурации очереди сообщений. Файл не соответствует шаблону
     * @return Ссылка на переменную
     */
    static const std::string& configWriterMessageFilePath_notMatch();

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
     * Прочитать тестовое сообщение
     * @return Тестовое сообщение
     */
    static const std::string& messageForTest();

    /**
     * Прочитать имя очереди
     * @return Ссылка на переменную
     */
    static const std::string &nameOfQueue();

    /**
     * Прочитать stop (для команды остановки приёма сообщений из очереди)
     * @return Ссылка на переменную
     */
    static const std::string &stop();

    /**
     * Прочитать максимальное количество сообщений в очереди.
     * @return Ссылка на переменную
     */
    static boost::interprocess::message_queue::size_type maxNumberOfMessages_100();

    /**
     * Прочитать максимальный размер сообщения в очереди
     * @return Ссылка на переменную
     */
    static boost::interprocess::message_queue::size_type maxMessageSize_1024();

    /**
     * Прочитать имя файла монитора
     * @return Ссылка на переменную
     */
    static const std::string &fileNameOfMonitor();

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
     * Прочитать признак логирования событий только в очередь
     * @return Ссылка на переменную
     */
    static const std::string& queue_only();

    /**
     * Прочитать/записать признак логирования событий в консоль
     * @return Ссылка на переменную
     */
    static const std::string& launchConsole_no();

    /**
     * Прочитать размер файла. Размер 200Б
     * @return Ссылка на переменную
     */
    static int size_200();

    /**
     * Прочитать количество файлов. 3 файла
     * @return Ссылка на переменную
     */
    static int numberFiles_3();

    /**
     * Время ожидания записи файла. 10 микросекунд
     * @return Время ожидания записи файла
     */
    static std::chrono::microseconds waitFileWrite_micro_10();

    /**
     * Прочитать время в секундах (1 секунда)
     * @return Время в секундах
     */
    static std::chrono::seconds seconds_1();

    /**
     * Прочитать время в секундах (3 секунды)
     * @return Время в секундах
     */
    static std::chrono::seconds seconds_3();

    /**
     * Прочитать количество посылок в очередь (10)
     * @return Время в секундах
     */
    static int numberOfPackagesInQueue_10();

    /**
     * Прочитать время в секундах (6 секунд в минутах)
     * @return Время в секундах
     */
    static std::chrono::duration<double, std::ratio<60>> seconds_6_in_minutes();

    /**
     * Прочитать время в секундах (6 секунд в часах)
     * @return Время в секундах
     */
    static std::chrono::duration<double, std::ratio<60 * 60>> seconds_6_in_hours();

    /**
     * Прочитать время в секундах (6 секунд в днях)
     * @return Время в секундах
     */
    static std::chrono::duration<double, std::ratio<60 * 60 * 24>> seconds_6_in_days();

    /**
     * Прочитать время в секундах (6 секунд в неделях)
     * @return Время в секундах
     */
    static std::chrono::duration<double, std::ratio<60 * 60 * 24 * 7>> seconds_6_in_weeks();

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



//Ожидать записи в файл
template <typename T>
void waitFileWrite(T value)
{
    while (true)
    {
        if (kav::Logger::isMessageRecorded())
        {
            std::this_thread::sleep_for(value);
        }
        else
        {
            break;
        }
    }
}

//Получить путь текущего файла логирования
std::string getLastFilePath();

//Перевести отметку времени в строку
std::string timePointToString(const std::chrono::system_clock::time_point& now);

//Получить отметку времени
std::string  getTimePoint();

//Получить строку лог-файл
std::string getLogLine(const std::string& timePoint);

//Соответствует ли фактический уровень логирования ожидаемому
bool isMatchingErrorLevel(const std::string& timePoint, const std::string& strErrorLevel);

//Соответствует ли фактический уровень логирования ожидаемому для исключения
bool isMatchingErrorLevelForException(const std::string& timePoint, const std::string& message, const std::string& strErrorLevel);

//Получить время из строки
std::chrono::system_clock::time_point getTimePointFromString(std::string& strLogLine);

//Получить время создания файла из имени файла, прочитав его первую запись
std::chrono::system_clock::time_point getFirstTimePointFromFile(std::string& fileName);

//Получить время последней записи в файл из имени файла
std::chrono::system_clock::time_point getLastTimePointFromFile(std::string& fileName);

#endif //KAV_LOGGER_TESTGENERAL_H
