//
// Created by Alexander on 09.03.2025.
//

#ifndef KAV_LOGGER_LOGGER_H
#define KAV_LOGGER_LOGGER_H



#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <filesystem>
#include <future>
#include <list>
#include <mutex>
#include <thread>
#include <vector>
#include <exception>


#include "kav/detail/types.h"
#include "kav/detail/monitorSender.h"
#include "kav/operationFileAndJSON.h"

#include "kav/detail/constants.h"



namespace kav
{

/**
 * Класс реализует исключение
 */
    class LoggerException : public std::exception
    {

    public:

        /**
         * Создать объект исключения
         * @param in_information Ссылка на информацию по ошибке
         */
        explicit LoggerException(const std::string &in_information = "")
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

}

namespace kav
{
    //Класс хранения переменных шаблонов JSON-объектов файлов
    class TemplatesJSONObjects
    {

    public:

        TemplatesJSONObjects() = delete;

        /**
         * Прочитать шаблон JSON-объекта файла logger.json
         * @return Ссылка на переменную
         */
        static const JSON &configLoggerTemplate()
        {
            //Значение по умолчанию
            static const JSON variable = JSON::parse(R"(
    {
    "usageTimeLimit" : {
        "seconds" : 0.0,
        "minutes" : 1.0,
        "hours" : 0.0,
        "days" : 0.0,
        "weeks" : 0.0
    },
    "storageTimeLimit" : {
        "seconds" : 0.0,
        "minutes" : 0.7,
        "hours" : 0.0,
        "days" : 0.0,
        "weeks" : 0.0
    },
    "dateTimeFormat" : "%Y-%m-%d %H:%M:%S",
    "fileNameFormat" : "%Y-%m-%d_%H-%M-%S",
    "fileSizeLimit" : 2000,
    "filesDirectory" : ".\\Logs\\"
}
    )");

            return variable;
        }

        /**
         * Прочитать шаблон JSON-объекта файла MessageQueue.json
         * @return Ссылка на переменную
         */
        static const JSON &configWriterMessageTemplate()
        {
            //Значение по умолчанию
            static const JSON variable = JSON::parse(R"(
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

            return variable;
        }

    };//TemplatesJSONObjects
}

namespace kav
{
    /**
     * Класс реализует логирование событий
     */
    class Logger
    {

    public:

        Logger(const Logger&) = delete;

    private:

        //Уровень логирования
        enum class Level
        {
            logger,
            debug,
            info,
            warning,
            error,
            fatal
        };

    public:

        /**
         * Создать объекты: СonfigLogger, WriterMessage. Настроить класс Logger и запустить в отдельном потоке запись сообщений
         * в лог-файл и отправку сообщений в монитор
         * @param in_configLoggerFilePath Путь файла конфигурации логирования
         * @param in_configWriterMessageFilePath Путь файла конфигурации очереди сообщений
         * @param in_launchConsole Признак логирования сообщения в консоль и запуска монитора
         */
        Logger(const std::string &in_configLoggerFilePath, const std::string &in_configWriterMessageFilePath, const std::string &in_launchConsole) try
                : configLogger(in_configLoggerFilePath), writerMessage(in_configWriterMessageFilePath, in_launchConsole)
        {
            //Объект класса не создан
            if (ptrToLogger == nullptr)
            {
                //Получить адрес объекта
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
        catch (OnlyOneObject& e)
        {
            //Выбросить исключение, так как более обного объекта создавать запрещено
            throw LoggerException(e.what());
        }
        catch (std::exception& e)
        {
            //Будет обработано в функциях выше
            throw LoggerException(e.what());
        }

        //Уведомить отдельный поток логирования о завершении работы и ожидать его окончания
        ~Logger() noexcept (false)
        {
            //Уведомить отдельный поток логирования о завершении работы
            stopLogger.store(true);

            //Вывести отдельный поток логирования из ожидания
            pushMessage = true;
            cvPushMessage.notify_one();

            try
            {
                //Ждать окончания работы отдельного потока логирования
                resultOfWriteToFileAndMonitor.get();
            }
            catch (std::exception& e)
            {
                //Будет обработано в функциях выше
                throw LoggerException(e.what());
            }
        }

        //Общие функции логирования

        /**
         * Записать сообщение уровня debug
         * @param message Ссылка на сообщение
         */
        static void debug(const std::string &message);

        /**
         * Записать сообщение уровня debug
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         */
        static void debug(const std::string &message, const std::exception &exception);

        /**
         * Записать сообщение уровня information
         * @param message Ссылка на сообщение
         */
        static void info(const std::string &message);

        /**
         * Записать сообщение уровня information
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         */
        static void info(const std::string &message, const std::exception &exception);

        /**
         * Записать сообщение уровня warning
         * @param message Ссылка на сообщение
         */
        static void warning(const std::string &message);

        /**
         * Записать сообщение уровня warning
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         */
        static void warning(const std::string &message, const std::exception &exception);

        /**
         * Записать сообщение уровня error
         * @param message Ссылка на сообщение
         */
        static void error(const std::string &message);

        /**
         * Записать сообщение уровня error
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         */
        static void error(const std::string &message, const std::exception &exception);

        /**
         * Записать сообщение уровня fatal
         * @param message Ссылка на сообщение
         */
        static void fatal(const std::string &message);

        /**
         * Записать сообщение уровня fatal
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         */
        static void fatal(const std::string &message, const std::exception &exception);

        /**
         * Изменить конфигурацию логгера
         * @param in_configLoggerFilePath Путь файла конфигурации логирования
         */
        static void reset(const std::string &in_configLoggerFilePath);

        /**
         * Записывается ли сообщение в файл и в монитор
         * @return Процесс записи сообщения в лог-файл и в монитор идёт
         */
        static bool isMessageRecorded();

        /**
         * Получить текущий путь лог-файла
         * @return Текущий путь лог-файла
         */
        //static const std::filesystem::path& getCurrentLogPath();



    private:

        /**
         * Класс реализует чтение и хранение параметров для настройки класса Logger
         */
        class ConfigLogger
        {

        public:

            /**
             * Инициализировать объект
             * @param in_configLoggerFilePath Ссылка на путь файла конфигурации логирования
             */
            explicit ConfigLogger(const std::string &in_configLoggerFilePath) : configLoggerFilePath{
                    in_configLoggerFilePath}
            {
                initialize();
            }

            /**
             * Получить интервал времени хранения файла
             * @return Количество недель
             */
            [[nodiscard]] double weeksStorage() const
            { return weeksStorageTime; }

            /**
             * Получить интервал времени хранения файла
             * @return Количество дней
             */
            [[nodiscard]] double daysStorage() const
            { return daysStorageTime; }

            /**
             * Получить интервал времени хранения файла
             * @return Количество часов
             */
            [[nodiscard]] double hoursStorage() const
            { return hoursStorageTime; }

            /**
             * Получить интервал времени хранения файла
             * @return Количество минут
             */
            [[nodiscard]] double minutesStorage() const
            { return minutesStorageTime; }

            /**
             * Получить интервал времени хранения файла
             * @return Количество секунд
             */
            [[nodiscard]] double secondsStorage() const
            { return secondsStorageTime; }

            /**
             * Получить интервал времени использования файла
             * @return Количество недель
             */
            [[nodiscard]] double weeksUsage() const
            { return weeksUsageTime; }

            /**
             * Получить интервал времени использования файла
             * @return Количество дней
             */
            [[nodiscard]] double daysUsage() const
            { return daysUsageTime; }

            /**
             * Получить интервал времени использования файла
             * @return Количество часов
             */
            [[nodiscard]] double hoursUsage() const
            { return hoursUsageTime; }

            /**
             * Получить интервал времени использования файла
             * @return Количество минут
             */
            [[nodiscard]] double minutesUsage() const
            { return minutesUsageTime; }

            /**
             * Получить интервал времени использования файла
             * @return Количество секунд
             */
            [[nodiscard]] double secondsUsage() const
            { return secondsUsageTime; }

            /**
             * Получить формат даты и времени записи в файл
             * @return Формат даты и времени
             */
            [[nodiscard]] const std::string &dateTimeFormat() const
            { return dateTimeFmt; }

            /**
             * Получить формат имени файл
             * @return Формат имени
             */
            [[nodiscard]] const std::string &fileNameFormat() const
            { return fileNameFmt; }

            /**
             * Получить предельный размер файла
             * @return Размер файла
             */
            [[nodiscard]] std::uint64_t fileSizeLimit() const
            { return fileSizeLmt; }

            /**
             * Получить директорию с лог-файлами
             * @return Директория с лог-файлами
             */
            [[nodiscard]] const std::string &filesDirectory() const
            { return filesDir; }

            /**
             * Изменить конфигурацию логгера
             * @param in_configLoggerFilePath Ссылка на путь файла конфигурации логирования
             */
            void reset(const std::string &in_configLoggerFilePath)
            {
                //Изменить путь файла конфигурации логирования
                configLoggerFilePath = in_configLoggerFilePath;
                //Инициализировать (настроить) класс
                initialize();
            }

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
            double weeksStorageTime{};
            //Интервал времени хранения файла, количество дней
            double daysStorageTime{};
            //Интервал времени хранения файла, количество часов
            double hoursStorageTime{};
            //Интервал времени хранения файла, количество минут
            double minutesStorageTime{};
            //Интервал времени хранения файла, количество секунд
            double secondsStorageTime{};

            //Интервалы времени использования файла

            //Интервал времени использования файла, количество недель
            double weeksUsageTime{};
            //Интервал времени использования файла, количество дней
            double daysUsageTime{};
            //Интервал времени использования файла, количество часов
            double hoursUsageTime{};
            //Интервал времени использования файла, количество минут
            double minutesUsageTime{};
            //Интервал времени использования файла, количество секунд
            double secondsUsageTime{};

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

            /**
             * Создать и настроить объекты: СonfigWriterMessage, MonitorSender
             * @param in_configWriterMessageFilePath Путь файла конфигурации очереди сообщений
             */
            explicit WriterMessage(const std::string &in_configWriterMessageFilePath, const std::string &in_launchConsole = Constants::default_launchConsole())
                    : configWriterMessage(in_configWriterMessageFilePath),
                      monitorSender(configWriterMessage.nameOfQueue(),
                                    configWriterMessage.maxNumberOfMessages(),
                                    configWriterMessage.maxMessageSize(),
                                    configWriterMessage.fileNameOfMonitor()),
                      launchConsole{in_launchConsole}
            {}

            /**
             * Записать в отдельном потоке информацию в файл и отправить в монитор
             */
            void run();

        private:

            /**
             * Класс реализует чтение и хранение параметров для настройки класса WriterMessage, MonitorSender
             */
            class ConfigWriterMessage
            {

            public:

                /**
                 * Инициализировать класс
                 * @param in_configWriterMessageFilePath Путь файла конфигурации очереди сообщений
                 */
                explicit ConfigWriterMessage(const std::string &in_configWriterMessageFilePath)
                        : configWriterMessageFilePath{in_configWriterMessageFilePath}
                {
                    initialize();
                }

                /**
                 * Получить имя очереди сообщений
                 * @return Имя очереди
                 */
                [[nodiscard]] const std::string &nameOfQueue() const
                { return nameOfQueueValue; }

                /**
                 * Получить максимальное количество сообщений в очереди
                 * @return Максимальное количество сообщений
                 */
                [[nodiscard]] boost::interprocess::message_queue::size_type maxNumberOfMessages() const
                { return maxNumberOfMessagesValue; }

                /**
                 * Получить максимальный размер сообщения
                 * @return Максимальный размер сообщения
                 */
                [[nodiscard]] boost::interprocess::message_queue::size_type maxMessageSize() const
                { return maxMessageSizeValue; }

                /**
                 * Получить имя файла основной программы
                 * @return Имя файла
                 */
                [[nodiscard]] const std::string &fileNameOfMainProgram() const
                { return fileNameOfMainProgramValue; }

                /**
                 * Получить имя файла монитора
                 * @return Имя файла
                 */
                [[nodiscard]] const std::string &fileNameOfMonitor() const
                { return fileNameOfMonitorValue; }

                /**
                 * Получить имя консоли
                 * @return Имя консоли
                 */
                [[nodiscard]] const std::string &nameOfConsole() const
                { return nameOfConsoleValue; }

                /**
                 * Получить признак запуска монитора
                 * @return Признак запуска
                 */
                [[nodiscard]] const std::string &indicatesMonitorStarting() const
                { return indicatesMonitorStartingValue; }

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

            //Признак логирования событий в консоль
            std::string launchConsole;


            /**
             * Ожидать запуска монитора (другого процесса)
             */
            void waitForMonitorToStart();

            /**
             * Определить, запущен ли процесс
             * @param processName Имя процесса
             * @return Процесс запущен (true)/не запущен (false)
             */
            static bool isProcessRun(const char *processName);

            /**
             * Запустить независимый процесс получения и вывода сообщений
             * @param lpApplicationName Имя процесса
             */
            static void startMonitor(LPCSTR lpApplicationName);

            /**
             * Обработать контейнер сообщений
             */
            void processMessageContainer();

            /**
             * Записать информацию в файл
             * @param messageForOutput Ссылка на сообщение для вывода
             */
            void writeToFile(std::string &&messageForOutput);

            /**
             * Отправить информацию в монитор в отдельном потоке
             * @param messageForOutput Ссылка на сообщение для вывода
             */
            void writeToMonitor(std::string &&messageForOutput);

        };


        //Объект чтения и хранения параметров для настройки класса Logger
        ConfigLogger configLogger;

        //Объект записи сообщений
        WriterMessage writerMessage;

        //Указатель на объект. Используется в статических функциях и классе Logger::WriterMessage
        inline static Logger *ptrToLogger{};

        //Типы интервалов времени

        //Интервал времени в секундах
        using Seconds = std::chrono::duration<double, std::ratio<1>>;
        //Интервал времени в минутах
        using Minutes = std::chrono::duration<double, std::ratio<60>>;
        //Интервал времени в часах
        using Hours = std::chrono::duration<double, std::ratio<60 * 60>>;
        //Интервал времени в днях
        using Days = std::chrono::duration<double, std::ratio<60 * 60 * 24>>;
        //Интервал времени в неделях
        using Weeks = std::chrono::duration<double, std::ratio<60 * 60 * 24 * 7>>;


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

        //Флаг процесса записи сообщения в лог-файл и в монитор
        std::atomic<bool> recordingMessage{true};


        /**
         * Настроить класс
         */
        void setup();



        //Вспомогательные функции инициализации и настройки класса

        /**
         * Записать сообщение уровня logger
         * @param message Ссылка на сообщение
         */
        static void logger(const std::string &message);

        /**
         * Записать сообщение уровня logger
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         */
        static void logger(const std::string &message, const std::exception &exception);

        /**
         * Определить файл для записи
         * @param directoryPath Путь к директории с логами
         */
        void identifyFile(const std::string &directoryPath);

        /**
         * Определить новый файл
         */
        void identifyNewFile();

        /**
         * Определить файлы по последнему изменению
         * @param directoryPath Ссылка на путь к директории с логами
         */
        void identifyFilesByLastModification();

        /**
         * Преобразовать момент времени одного типа в другой
         * @tparam TP Тип момента времени
         * @param tp Момент времени преобразующегося типа
         * @return Момент времени проеобразованного типа
         */
        template<typename TP>
        std::time_t to_time_t(TP tp)
        {
            auto sctp = time_point_cast<std::chrono::system_clock::duration>(tp - TP::clock::now() + std::chrono::system_clock::now());
            return std::chrono::system_clock::to_time_t(sctp);
        }

        /**
         * Определить, превышено ли время использования файла
         * @return Превышено (true)/ Непревышено (false)
         */
        bool isFileUsageTimeExceeded();

        /**
         * Удалить файлы по сроку хранения
         */
        void deleteFilesByRetentionPeriod(const std::string& directoryPath);



        //Основные функции логирования (формирование сообщения)

        /**
         * Записать информацию в контейнер сообщений
         * @param level Уровень логирования
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         */
        void log(Level level, const std::string &message, const std::exception &exception);

        /**
         * Сформировать сообщение для вывода
         * @param level Уровень логирования
         * @param message Ссылка на сообщение
         * @param exception Ссылка на исключение
         * @param timeEvent Текущее время
         * @return Сообщение для вывода
         */
        std::string generateMessageForOutput(Level level, const std::string &message, const std::exception &exception,
                                             std::chrono::system_clock::time_point &timeEvent);

        /**
         * Получить из уровня логирования строку
         * @param level Уровень логирования
         * @return Строка
         */
        static std::string levelToString(Level level);

        /**
         * Перевести время создания файла в строку
         * @param timePoint Текущее время
         * @return Строка времени создания файла
         */
        std::string timePointToString(const std::chrono::system_clock::time_point &timePoint);



        //Вспомогательные классы

        /**
         * Класс реализует иключение-заглушку
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
            [[nodiscard]] const char *what() const noexcept override
            {
                return "Exception-stub";
            }

            /**
             * Получить код исключения
             * @return Код исключения
             */
            [[nodiscard]] static ErrorCodeStub getErrorCode()
            {
                return ERROR_STUB;
            }

        };

        /**
         * Класс реализует исключение о невозможности создания более одного объекта
         */
        class OnlyOneObject : public std::exception
        {

        public:

            /**
             * Получить информацию по исключению
             * @return Информация по исключению
             */
            [[nodiscard]] const char *what() const noexcept override
            {
                return "There should be only one object of the Logger class";
            }

        };

    };
}



#endif //KAV_LOGGER_LOGGER_H



