//
// Created by Alexander on 09.03.2025.
//

#ifndef SEARCH_ENGINE_LOGGER_H
#define SEARCH_ENGINE_LOGGER_H



#include <atomic>
#include <iostream>
#include <string>
#include <filesystem>
#include <future>
#include <list>
#include <mutex>
#include <thread>
#include <vector>

#include "check/checkFileException.h"
#include "general.h"
#include "monitorSender.h"



//Шаблон JSON-объекта файла logger.json
const JSON configLoggerTemplate = JSON::parse(R"(
    {
    "usageTimeLimit" : {
        "seconds" : 0,
        "minutes" : 1,
        "hours" : 0,
        "days" : 0,
        "weeks" : 0
    },
    "storageTimeLimit" : {
        "seconds" : 0,
        "minutes" : 7,
        "hours" : 0,
        "days" : 0,
        "weeks" : 0
    },
    "dateTimeFormat" : "%Y-%m-%d %H:%M:%S",
    "fileNameFormat" : "%Y-%m-%d_%H-%M-%S",
    "fileSizeLimit" : 2000,
    "filesDirectory" : ".\\Logs\\"
}
    )");

//Шаблон JSON-объекта файла MessageQueue.json
const JSON configWriterMessageTemplate = JSON::parse(R"(
    {
    "messageQueue" : {
        "nameOfQueue" : "search_engine",
        "maxNumberOfMessages" : 100,
        "maxMessageSize" : 256,
        "fileNameOfMainProgram" : "search_engine.exe",
        "fileNameOfMonitor" : "search_engine_monitor.exe",
        "nameOfConsole" : "Logger Monitor",
        "indicatesMonitorStarting" : "C:\\Windows\\Temp\\search_engine_monitor"
    }
    }
    )");



/**
 * Класс реализует логирование событий
 */
class Logger
{

private:

    //Уровень логирования
    enum class Level
    {
        debug,
        info,
        warning,
        error,
        fatal
    };

public:

    Logger(const std::string &in_configLoggerFilePath, const std::string &in_configWriterMessageFilePath)
        : configLogger(in_configLoggerFilePath), writerMessage(in_configWriterMessageFilePath)
    {
        //Объект класса не создан
        if (ptrToLogger == nullptr)
        {
            ptrToLogger = this;

            //Настроить класс
            setup();

            //Запустить в отдельном потоке запись сообщения в лог-файл и отправку сообщения в монитор
            resultOfWriteToFileAndMonitor = std::async(&Logger::WriterMessage::run, &writerMessage);
        }
        else
        {
            //Выбросить исключение, так как более обного объекта создавать запрещено
            throw OnlyOneObject();
        }
    }

    ~Logger()
    {
        //Уведомить отдельный поток логирования о завершении работы
        stopLogger.store(true);

        //Вывести отдельный поток логирования из ожидания
        pushMessage = true;
        cvPushMessage.notify_one();

        //Ждать окончания работы отдельного потока логирования
        resultOfWriteToFileAndMonitor.wait();
    }



    //Общие функции логирования

    /**
     * Записать сообщение уровня debug
     * @param message Ссылка на сообщение
     */
    static void debug(const std::string& message);

    /**
     * Записать сообщение уровня debug
     * @param message Сообщение
     * @param exception Исключение
     */
    static void debug(const std::string& message, const std::exception& exception);

    /**
     * Записать сообщение уровня information
     * @param message Сообщение
     */
    static void info(const std::string& message);

    /**
     * Записать сообщение уровня information
     * @param message Сообщение
     * @param exception Исключение
     */
    static void info(const std::string& message, const std::exception& exception);
    
    /**
     * Записать сообщение уровня warning
     * @param message Сообщение
     */
    static void warning(const std::string& message);

    /**
     * Записать сообщение уровня warning
     * @param message Сообщение
     * @param exception Исключение
     */
    static void warning(const std::string& message, const std::exception& exception);

    /**
     * Записать сообщение уровня error
     * @param message Сообщение
     */
    static void error(const std::string& message);

    /**
     * Записать сообщение уровня error
     * @param message Сообщение
     * @param exception Исключение
     */
    static void error(const std::string& message, const std::exception& exception);

    /**
     * Записать сообщение уровня fatal
     * @param message Сообщение
     */
    static void fatal(const std::string& message);

    /**
     * Записать сообщение уровня fatal
     * @param message Сообщение
     * @param exception Исключение
     */
    static void fatal(const std::string& message, const std::exception& exception);

private:

    /**
     * Класс реализует чтение и хранение параметров для настройки класса Logger
     */
    class ConfigLogger
    {

    public:

        explicit ConfigLogger(const std::string &in_configLoggerFilePath) : configLoggerFilePath{in_configLoggerFilePath}
        {
            initialize();
        }

        [[nodiscard]] std::int64_t weeksStorage() const {return weeksStorageTime;}
        [[nodiscard]] std::int64_t daysStorage() const {return daysStorageTime;}
        [[nodiscard]] std::int64_t hoursStorage() const {return hoursStorageTime;}
        [[nodiscard]] std::int64_t minutesStorage() const {return minutesStorageTime;}
        [[nodiscard]] std::int64_t secondsStorage() const {return secondsStorageTime;}

        [[nodiscard]] std::int64_t weeksUsage() const {return weeksUsageTime;}
        [[nodiscard]] std::int64_t daysUsage() const {return daysUsageTime;}
        [[nodiscard]] std::int64_t hoursUsage() const {return hoursUsageTime;}
        [[nodiscard]] std::int64_t minutesUsage() const {return minutesUsageTime;}
        [[nodiscard]] std::int64_t secondsUsage() const {return secondsUsageTime;}

        [[nodiscard]] const std::string& dateTimeFormat() const {return dateTimeFmt;}
        [[nodiscard]] const std::string& fileNameFormat() const {return fileNameFmt;}
        [[nodiscard]] std::uint64_t fileSizeLimit() const {return fileSizeLmt;}
        [[nodiscard]] const std::string& filesDirectory() const {return filesDir;}

    private:

        //Путь файла конфигурации логирования
        std::string configLoggerFilePath;
        //JSON-объект конфигурации логирования
        JSON configLoggerJSON;

        /**
         * Инициализировать (настроить) класс
         */
        void initialize();

        //Интервалы времени хранения файла

        //Интервал времени хранения файла, количество недель
        std::int64_t weeksStorageTime{};
        //Интервал времени хранения файла, количество дней
        std::int64_t daysStorageTime{};
        //Интервал времени хранения файла, количество часов
        std::int64_t hoursStorageTime{};
        //Интервал времени хранения файла, количество минут
        std::int64_t minutesStorageTime{};
        //Интервал времени хранения файла, количество секунд
        std::int64_t secondsStorageTime{};

        //Интервалы времени использования файла

        //Интервал времени использования файла, количество недель
        std::int64_t weeksUsageTime{};
        //Интервал времени использования файла, количество дней
        std::int64_t daysUsageTime{};
        //Интервал времени использования файла, количество часов
        std::int64_t hoursUsageTime{};
        //Интервал времени использования файла, количество минут
        std::int64_t minutesUsageTime{};
        //Интервал времени использования файла, количество секунд
        std::int64_t secondsUsageTime{};

        //Формат даты и времени записи в файл
        std::string dateTimeFmt{};
        //Формат имени файла
        std::string fileNameFmt{};
        //Предельный размер файла
        std::uint64_t fileSizeLmt{};
        //Директория с лог-файлами
        std::string filesDir{};

    };

    /**
     * Класс реализует запись сообщений в лог-файл и монитор
     */
    class WriterMessage
    {

    public:

        explicit WriterMessage(const std::string& in_configWriterMessageFilePath)
            : configWriterMessage(in_configWriterMessageFilePath),
              monitorSender(configWriterMessage.nameOfQueue(),
                            configWriterMessage.maxNumberOfMessages(),
                            configWriterMessage.maxMessageSize(),
                            configWriterMessage.fileNameOfMonitor())
        {}

        /**
         * Записать информацию в файл и отправить информацию в монитор в отдельном потоке
         */
        void run();

    private:

        /**
         * Класс реализует чтение и хранение параметров для настройки класса WriterMessage, MonitorSender
         */
        class ConfigWriterMessage
        {

        public:

            explicit ConfigWriterMessage(const std::string &in_configWriterMessageFilePath) : configWriterMessageFilePath{in_configWriterMessageFilePath}
            {
                initialize();
            }

            [[nodiscard]] const std::string& nameOfQueue() const {return nameOfQueueValue;}
            [[nodiscard]] boost::interprocess::message_queue::size_type maxNumberOfMessages() const {return maxNumberOfMessagesValue;}
            [[nodiscard]] boost::interprocess::message_queue::size_type maxMessageSize() const {return maxMessageSizeValue;}
            [[nodiscard]] const std::string& fileNameOfMainProgram() const {return fileNameOfMainProgramValue;}
            [[nodiscard]] const std::string& fileNameOfMonitor() const {return fileNameOfMonitorValue;}

            [[nodiscard]] const std::string& nameOfConsole() const {return nameOfConsoleValue;}
            [[nodiscard]] const std::string& indicatesMonitorStarting() const {return indicatesMonitorStartingValue;}

        private:

            //Путь файла конфигурации логирования
            std::string configWriterMessageFilePath;
            //JSON-объект конфигурации логирования
            JSON configWriterMessageJSON;

            /**
             * Инициализировать (настроить) класс
             */
            void initialize();

            //Имя очереди
            std::string nameOfQueueValue{};
            //Максимальное количество сообщений в очереди
            boost::interprocess::message_queue::size_type maxNumberOfMessagesValue{};
            //Максимальный размер сообщения
            boost::interprocess::message_queue::size_type maxMessageSizeValue{};
            //Имя файла основной программы
            std::string fileNameOfMainProgramValue{};
            //Имя файла монитора
            std::string fileNameOfMonitorValue{};
            //Имя консоли
            std::string nameOfConsoleValue{};
            //Признак запуска монитора
            std::string indicatesMonitorStartingValue{};

        };



        //Объект чтения и хранения параметров для настройки класса Logger
        ConfigWriterMessage configWriterMessage;

        //Объект монитора отправки сообщений
        MonitorSender monitorSender;

        //Контейнер текущих сообщений
        std::list<std::string> messages;



        /**
         * Ожидать запуска монитора (другого процесса)
         */
        void waitForMonitorToStart();

        /**
         * Определить, запущен ли процесс
         * @param processName Имя процесса
         * @return Процесс запущен (true)/не запущен (false)
         */
        bool isProcessRun(const char * processName);

        /**
         * Запустить независимый процесс получения и вывода сообщений
         * @param lpApplicationName Имя процесса
         */
        void startMonitor(LPCSTR lpApplicationName);

        /**
         * Обработать контейнер сообщений
         */
        void processMessageContainer();

        /**
         * Записать информацию в файл
         * @param messageForOutput Ссылка на сообщение для вывода
         */
        void writeToFile(const std::string& messageForOutput);

        /**
         * Отправить информацию в монитор в отдельном потоке
         * @param messageForOutput Ссылка на сообщение для вывода
         * @param monitorSender Ссылка на объект класса отправки сообщений для вывода на монитор
         */
        void writeToMonitor(const std::string& messageForOutput);

    };


    //Объект чтения и хранения параметров для настройки класса Logger
    ConfigLogger configLogger;

    //Объект записи сообщений
    WriterMessage writerMessage;

    //Указатель на объект. Используется в статических функциях и классе Logger::WriterMessage
    inline static Logger* ptrToLogger{};

    //Типы интервалов времени

    //Интервал времени в секундах
    using Seconds = std::chrono::duration<int64_t, std::ratio<1>>;
    //Интервал времени в минутах
    using Minutes = std::chrono::duration<int64_t, std::ratio<60>>;
    //Интервал времени в часах
    using Hours = std::chrono::duration<int64_t, std::ratio<60*60>>;
    //Интервал времени в днях
    using Days = std::chrono::duration<int64_t, std::ratio<60*60*24>>;
    //Интервал времени в неделях
    using Weeks = std::chrono::duration<int64_t, std::ratio<60*60*24*7>>;



    //Текущий файл для записи
    std::filesystem::path file{};

    //Контейнер пар пути и момента времени последнего изменения файла
    std::vector<std::pair<std::filesystem::path, std::chrono::system_clock::time_point>> logs{};



    //Переменные для работы отдельного потока логирования

    //Контейнер сообщений. Используется для накапливания сообщений и чтения их отдельным потоком логирования
    std::list<std::string> messages;

    //Результат работы отдельного потока записи сообщения в лог-файл и отправки сообщения в монитор
    std::future<void> resultOfWriteToFileAndMonitor;

    //Мьютекс чтения-записи контейнера сообщений основным потоком и отдельного потока логирования
    std::mutex mutReadWriteMessages;

    //Сигнал о добавлении сообщения в контейнер сообщений
    std::condition_variable cvPushMessage;
    //Подтверждение добавления сообщения в контейнер сообщений
    bool pushMessage{};

    //Уведомление о завершении работы отдельного потока логирования
    std::atomic<bool> stopLogger{false};



    /**
     * Настроить класс
     */
    void setup();



    //Вспомогательные функции инициализации и настройки класса

    /**
     * Определить файл для записи
     * @param directoryPath Путь к директории с логами
     */
    void identifyFile(const std::string& directoryPath);

    /**
     * Определить новый файл
     */
    void identifyNewFile();

    /**
     * Определить файлы по последнему изменению
     * @param directoryPath Ссылка на путь к директории с логами
     */
    void identifyFilesByLastModification(const std::string& directoryPath);

    /**
     * Преобразовать момент времени одного типа в другой
     * @tparam TP Тип момента времени
     * @param tp Момент времени преобразующегося типа
     * @return Момент времени проеобразованного типа
     */
    template <typename TP>
    std::time_t to_time_t(TP tp)
    {
        using namespace std::chrono;
        auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                            + system_clock::now());
        return system_clock::to_time_t(sctp);
    }

    /**
     * Определить, превышено ли  время использования файла
     * @return Превышено (true)/ Непревышено (false)
     */
    bool isFileUsageTimeExceeded();

    /**
     * Удалить файлы по сроку хранения
     */
    void deleteFilesByRetentionPeriod();



    //Основные функции логирования (формирование сообщения)

    /**
     * Записать информацию в лог-файл
     * @param level Уровень логирования
     * @param message Ссылка на сообщение
     * @param exception Ссылка на исключение
     */
    void log(Level level, const std::string& message, const std::exception& exception);

    /**
     * Сформировать сообщение для вывода
     * @param level Уровень логирования
     * @param message Сообщение
     * @param exception Исключение
     * @param timeEvent Текущее время
     * @return Сообщение для вывода
     */
    std::string generateMessageForOutput(Level level, const std::string& message, const std::exception& exception, std::chrono::system_clock::time_point& timeEvent);

    /**
     * Получить из уровня логирования строку
     * @param level Уровень логирования
     * @return Строка
     */
    std::string levelToString(Level level);

    /**
     * Перевести время создания файла в строку
     * @param timePoint Текущее время
     * @return Строка времени создания файла
     */
    std::string timePointToString(const std::chrono::system_clock::time_point& timePoint);



    //Вспомогательные классы

    /**
     * Класс реализует генерацию исключения-заглушки
     */
    class ExceptionStub : public std::exception
    {

    private:

        enum ErrorCodeStub
        {
            ERROR_STUB = 1
        };

    public:

        /**
         * Получить информацию по исключению
         * @return Информация по исключению
         */
        [[nodiscard]] const char* what() const noexcept override
        {
            return "Exception-stub";
        }

        /**
         * Получить код исключения
         * @return Код исключения
         */
        [[nodiscard]] ErrorCodeStub getErrorCode() const
        {
            return ERROR_STUB;
        }

    };

    /**
     * Класс реализует генерацию исключения о невозможности создания более одного объекта
     */
    class OnlyOneObject : public std::exception
    {

    public:

        /**
         * Получить информацию по исключению
         * @return Информация по исключению
         */
        [[nodiscard]] const char* what() const noexcept override
        {
            return "There should be only one object of the Logger class.";
        }

    };

};



#endif //SEARCH_ENGINE_LOGGER_H



