//
// Created by Alexander on 13.06.2025.
//

#ifndef SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H
#define SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H


#include <atomic>

#include "kav/operationFileAndJSON.h"
#include "kav/logger.h"
#include "types.h"



/**
 * Уровни логирования
 */
enum class ErrorLevel
{
    no_level,
    debug,
    info,
    warning,
    error,
    fatal
};

/**
 * Коды ошибок работы с файлами
 */
enum class ErrorCode
{
    no_error,
    error_file_missing,
    error_file_not_open_read,
    error_file_not_read,
    error_file_not_open_write,
    error_file_not_write,
    error_json_structure_corrupted,
    error_json_structure_not_match,
    error_array_empty,
    error_file_paths_array_empty,
    error_requests_array_empty,
    error_all_files_not_read,
    error_any_files_not_read
};

/**
 * Описание кодов ошибок
 */
static const std::map<ErrorCode, std::string> descriptionErrorCode{

        {ErrorCode::no_error,                       ""},
        {ErrorCode::error_file_missing,             "This file is missing"},
        {ErrorCode::error_file_not_open_read,       "This file cannot be opened for reading"},
        {ErrorCode::error_file_not_read,            "This file has not been read"},
        {ErrorCode::error_file_not_open_write,      "This file cannot be opened for writing"},
        {ErrorCode::error_file_not_write,           "This file has not been write"},
        {ErrorCode::error_json_structure_corrupted, "The structure of this file is corrupted"},
        {ErrorCode::error_json_structure_not_match, "The structure of this file does not match the required one"},
        {ErrorCode::error_array_empty,              "The array is empty"},
        {ErrorCode::error_file_paths_array_empty,   "The array paths of this file is empty"},
        {ErrorCode::error_requests_array_empty,     "The array requests of this file is empt"},
        {ErrorCode::error_all_files_not_read,       "All files have not been read"},
        {ErrorCode::error_any_files_not_read,       "Any files have not been read"}
};

/**
 * Структура результатов чтения текстовых файлов (одновременное чтение в нескольких потоках)
 */
struct ResultOfReadMultipleTextFiles
{

    /**
     * Пара контейнеров текстов и кодов ошибок
     */
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documentsAndErrors;

    /**
     * Количество непрочитанных документов
     */
    std::size_t errorNumber{};

    /**
     * Код общей ошибки
     */
    ErrorCode errorCode;

};

/**
 * Класс реализует диспетчер операций c файлами и JSON-объектами
 * Выполняет операции с файлами (чтение-запись), проверку JSON-объекта и при необходимости определяет уровень логирования,
 * и логирует события, по имени вызывающей функции при ошибке операции.
 */
class DispatcherOperations
{

private:

    /**
     * Класс реализует исключение
     */
    class OperationException : public std::exception
    {

    public:

        /**
         * Инициализирует код исключения
         * @param in_errorCode Код ошибки
         * @param in_information Ссылка на информацию по ошибке
         */
        explicit OperationException(const std::string &in_information)
        {
            information = in_information;
        }

        /**
         * Получить информацию по исключению
         * @return Информация по исключению
         */
        [[nodiscard]] const char *what() const noexcept override
                {
                        return information.c_str();
                }

    private:

        //Информация по ошибке
        std::string information;

    };

public:

    DispatcherOperations() = delete;

    /**
      * Записать JSON-файл
      * @param filePath Ссылка на путь JSON-файла
      * @param objectJSON Ссылка на JSON-объект для записи
      * @param formatByWidth Ширина отступа
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode writeJSONFile(
            const std::string &filePath,
            const JSON &objectJSON,
            const unsigned int formatByWidth = 2,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Проверить JSON-структуру на соответствие шаблону
      * @param filePath Ссылка на путь JSON-файла
      * @param objectJSON Ссылка на JSON-объект для проверки
      * @param objectJSONTemplate Ссылка на JSON-объект шаблона
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode checkJSONStructureMatch(
            const std::string &filePath,
            const JSON &objectJSON, const JSON &objectJSONTemplate,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Проверить массив JSON-объекта путей файлов на пустоту
      * @param objectJSON Ссылка на JSON-объект для проверки
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode checkFilePathsArray(
            const JSON &objectJSON,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Проверить массив JSON-объекта запросов на пустоту
      * @param objectJSON Ссылка на JSON-объект для проверки
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Код ошибки
      */
    static ErrorCode checkRequestsArray(
            const JSON &objectJSON,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать JSON-файл
      * @param filePath Ссылка на путь JSON-файла
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара JSON-объекта и кода ошибки
      */
    static std::pair<JSON, ErrorCode> readJSONFile(
            const std::string &filePath,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать текстовый файл
      * @param filePath Ссылка на путь текстового файла
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара текста и кода ошибки
      */
    static std::pair<std::string, ErrorCode> readTextFile(
            const std::string &filePath,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать несколько текстовых файлов одновременно в разных потоках
      * @param filePaths Ссылка на путь контейнера путей файлов
      * @param desiredNumberOfThreads Желаемое количество потоков
      * @param maximumAllowableErrorsNumber Максимально возможное количество ошибок
      * @param errorLevelOneFile Уровень логирования для одного фойла
      * @param errorLevelMultipleFiles Уровень логирования для всех файлов
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Структура результатов чтения текстовых файлов
      */
    static ResultOfReadMultipleTextFiles readMultipleTextFiles(
            const std::vector<std::string>& filePaths,
            const unsigned int desiredNumberOfThreads = std::thread::hardware_concurrency(),
            const std::size_t maximumAllowableErrorsNumber = 0,
            const std::string& message = "",
            ErrorLevel errorLevelOneFile = ErrorLevel::no_level, ErrorLevel errorLevelMultipleFiles = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать несколько текстовых файлов последовательно
      * @param filePath Ссылка на путь текстового файла
      * @param filesNumber Количество файлов
      * @param packageID ID пакета для разных потоков
      * @param maximumAllowableErrorsNumber Максимально возможное количество ошибок
      * @param errorLevelOneFile Уровень логирования для одного фойла
      * @param errorLevelMultipleFiles Уровень логирования для всех файлов
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара текста и кода ошибки
      */
    static std::pair<std::string, ErrorCode> readMultipleTextFilesSequentially(
            const std::string& filePath,
            const std::size_t filesNumber,
            const std::size_t maximumAllowableErrorsNumber = 0,
            const std::size_t packageID = 0,
            const std::string& message = "",
            ErrorLevel errorLevelOneFile = ErrorLevel::no_level, ErrorLevel errorLevelMultipleFiles = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    //Для тестирования передачи контейнера по ссылке
    /*static void readTextFileRef(
            const std::string &filePath,
            std::string &document,
            const std::string &message = "",
            ErrorCode &errorCode, ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);*/

    //Для тестирования передачи контейнера по ссылке
    /*static void readMultipleTextFilesImplRef(
            const std::vector<std::string>& filePaths,
            std::pair<std::vector<std::string>, std::vector<ErrorCode>> &documents,
            const std::string &message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);*/

    //Для тестирования передачи контейнера по ссылке
    /*static void readMultipleTextFilesRef(
            const std::vector<std::string>& filePaths,
            ResultOfReadMultipleTextFiles &documents,
            std::size_t maximumAllowableErrorsNumber = 1,
            const std::string& message = "",
            ErrorLevel errorLevelOneFile = ErrorLevel::no_level, ErrorLevel errorLevelMultipleFiles = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);*/

private:

    /**
      * Прочитать несколько текстовых файлов одновременно в разных потоках
      * @param filePaths Ссылка на путь контейнера путей файлов
      * @param desiredNumberOfThreads Желаемое количество потоков
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара контейнеров текстов и кодов ошибок
      */
    static std::pair<std::vector<std::string>, std::vector<ErrorCode>> readMultipleTextFilesImpl(
            const std::vector<std::string>& filePaths,
            const unsigned int desiredNumberOfThreads,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
      * Прочитать текстовый файл из множества файлов. Функция нужна для косвенного определения уровня логирования
      * @param filePath Ссылка на путь текстового файла
      * @param errorLevel Уровень логирования
      * @param message Ссылка на сообщение
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара текста и кода ошибки
      */
    static std::pair<std::string, ErrorCode> readTextFileFromMultipleFiles(
            const std::string &filePath,
            const std::string& message = "",
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Определить код ошибки и уровень логирования для множества файлов
     * @param filesNumber Количество файлов
     * @param errorNumber Количество ошибок
     * @param maximumAllowableErrorsNumber Максимально возможное количество ошибок
     * @param errorLevelOneFile Уровень логирования для одного фойла
     * @param errorLevelMultipleFiles Уровень логирования для всех файлов
     * @param callingFunction Ссылка на вызывающую функцию
     * @return Пара кода ошибки и уровня логирования для всех файлов
     */
    static std::pair<ErrorCode, ErrorLevel> determineErrorCodeAndErrorLevelForMultipleFiles(
            const std::size_t filesNumber,
            const std::size_t errorNumber, const std::size_t maximumAllowableErrorsNumber,
            ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
            const boost::source_location &callingFunction);

    /**
     * Преобразовать код ошибки из внешней функции во внутренний код ошибки
     * @param errorCode Код ошибки из внешней функции
     * @return Код ошибки внутренний
     */
    static ErrorCode convertErrorCodeFrom(const kav::ErrorCode errorCode);

    /**
     * Получить уровень логирования на основе вызывающей функции
     * @param functionName Ссылка на имя функции
     * @return Уровень логировани
     */
    static ErrorLevel getErrorLevelFrom(const std::string& functionName);

    /**
     * Получить имя функции вида "имя_класса::имя_функции"
     * @param callingFunction Ссылка на вызывающую функцию
     * @return Имя функции
     */
    static std::string getFunctionName(const boost::source_location &callingFunction);

    /**
     * Получить уровень логирования из объекта предоставленного BOOST_CURRENT_LOCATION
     * @param callingFunctionStr Ссылка на объект предоставленный BOOST_CURRENT_LOCATION
     * @return Уровень логирования
     */
    static ErrorLevel getErrorLevel(const boost::source_location &callingFunction);

    /**
     * Определить количество потоков
     * @param filePaths Ссылка на путь контейнера путей файлов
     * @param desiredNumberOfThreads Желаемое количество потоков
     * @return Пара количества документов для одного потока и фактическое количество потоков
     */
    static std::pair<std::size_t, const unsigned int> countNumberOfThreads(const std::vector<std::string> &filePaths, const unsigned int desiredNumberOfThreads);

    /**
     * Подсчитать количество непрочитанных документов
     * @param errors Ссылка на контейнер кодов ошибок
     * @return Количество непрочитанных документов
     */
    static std::size_t countErrorsNumber(std::vector<ErrorCode> &errors);

    /**
     * Логировать событие по коду ошибки и уровню логирования
     * @param filePath Ссылка на путь к файлу
     * @param errorCode Код ошибки
     * @param errorLevel Уровень логирования
     * @param message Ссылка на сообщение
     * @param callingFunction Ссылка на вызывающую функцию
     */
    static void determineValidity(
            const std::string &filePath,
            ErrorCode errorCode = ErrorCode::no_error,
            ErrorLevel errorLevel = ErrorLevel::no_level,
            const std::string& message = "",
            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    /**
     * Контейнер соответствия имени вызывающей функции и, ID пакета (для отделения разных наборов файлов в потоках) и текущим количествам файлов и ошибок.
     * Используется в функции readMultipleTextFilesSequentially
     */
    inline static std::map<std::string, //Имя функции, вида "DispatcherOperations::readMultipleTextFilesSequentially"
                           std::map<
                                    std::size_t, //ID пакета (для отделения разных наборов файлов в потоках)
                                    std::pair<
                                              std::atomic<std::size_t>, std::atomic<std::size_t> //Текущее количество файлов и ошибок в пакете
                                             >
                                   >
                          > currentErrorsNumber{};

    /**
     * Мьютекс на поиск и добавление ID пакета в контейнер соответствия
     */
    inline static std::mutex mutexFindAddPackageID;

};



#endif //SEARCH_ENGINE_DISPATCHERDETERMINEVALIDITY_H/
