//
// Created by Alexander on 09.03.2025.
//

#ifndef SEARCH_ENGINE_LOGGER_H
#define SEARCH_ENGINE_LOGGER_H



#include <atomic>
#include <string>
#include <filesystem>
#include <future>
#include <list>
#include <mutex>
#include <thread>
#include <vector>

#include "checkFileException.h"
#include "general.h"
#include "monitorSender.h"



/**
  * Запустить независимый процесс получения и вывода сообщений
  * @param lpApplicationName Имя процесса
  */
void startMonitor(LPCSTR lpApplicationName);

/**
 * Класс реализует логирование событий
 */
class Logger
{

private:

    //Уровень логирования
    enum class Level
    {
        L_DEBUG_L,
        L_INFO_L,
        L_WARNING_L,
        L_ERROR_L,
        L_FATAL_L
    };

public:

    explicit Logger(const std::string &configFilePath)
    {
        //Условие, ограничивающее создание более одного объекта
        if (selfObject != nullptr) throw std::runtime_error("It is impossible to create an object!");

        selfObject = this;

        //Инициализировать (настроить) класс
        initialize(configFilePath);

        //Запустить в отдельном потоке запись сообщения в лог-файл и отправку сообщения в монитор
        resultOfWriteToFileAndMonitor = std::async(&Logger::writeToFileAndMonitor, this);


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


    //Указатель на свой объект. Используется для обращения к объекту из статических функций
    inline static Logger *selfObject{};

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

    //Интервалы времени хранения файла

    //Интервал времени хранения файла, количество недель
    static inline std::int64_t weeksStorage{};
    //Интервал времени хранения файла, количество дней
    static inline std::int64_t daysStorage{};
    //Интервал времени хранения файла, количество часов
    static inline std::int64_t hoursStorage{};
    //Интервал времени хранения файла, количество минут
    static inline std::int64_t minutesStorage{};
    //Интервал времени хранения файла, количество секунд
    static inline std::int64_t secondsStorage{};

    //Интервалы времени использования файла

    //Интервал времени использования файла, количество недель
    static inline std::int64_t weeksUsage{};
    //Интервал времени использования файла, количество дней
    static inline std::int64_t daysUsage{};
    //Интервал времени использования файла, количество часов
    static inline std::int64_t hoursUsage{};
    //Интервал времени использования файла, количество минут
    static inline std::int64_t minutesUsage{};
    //Интервал времени использования файла, количество секунд
    static inline std::int64_t secondsUsage{};

    //Форматы даты, времени, имени файла

    //Формат даты и времени записи в файл
    static inline std::string dateTimeFormat{};
    //Формат имени файла
    static inline std::string fileNameFormat{};

    //Предельный размер файла
    static inline  uint64_t fileSizeLimit{};

    //Директория с лог-файлами
    static inline std::string filesDirectory{};

    //Параметры основного процесса и монитора

    //Имя очереди
    static inline std::string nameOfQueue{};
    //Максимальное количество сообщений в очереди
    static inline boost::interprocess::message_queue::size_type maxNumberOfMessages{};
    //Максимальный размер сообщения
    static inline boost::interprocess::message_queue::size_type maxMessageSize{};
    //Имя файла основной программы
    static inline std::string fileNameOfMainProgram{};
    //Имя файла монитора
    static inline std::string fileNameOfMonitor{};
    //Имя консоли
    static inline std::string nameOfConsole{};
    //Признак запуска монитора
    static inline std::string indicatesMonitorStarting{};

    //Файл для записи
    static inline std::filesystem::path file{};

    //Контейнер пар пути и момента времени последнего изменения файла
    inline static std::vector<std::pair<std::filesystem::path, std::chrono::system_clock::time_point>> logs{};

    //Переменные для работы отдельного потока логирования

    //Контейнер сообщений. Используется для накапливания сообщений и чтения их отдельным потоком логирования
    inline static std::list<std::string> messages;

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



    //Функции инициализации и настройки класса

    /**
     * Инициализировать (настроить) класс
     * @param configFilePath Ссылка на файл конфигурации логирования
     */
    static void initialize(const std::string& configFilePath);

    /**
     * Инициализировать переменные
     * @param configJSON JSON-объект содержащий значения
     */
    static void initializeVariables(const JSON& configJSON);

    /**
     * Настроить класс
     */
    static void setupClass();



    //Вспомогательные функции инициализации и настройки класса

    /**
     * Определить файл для записи
     * @param directoryPath Путь к директории с логами
     */
    static void identifyFile(const std::string& directoryPath);

    /**
     * Определить новый файл
     */
    static void identifyNewFile();

    /**
     * Определить файлы по последнему изменению
     * @param directoryPath Ссылка на путь к директории с логами
     */
    static void identifyFilesByLastModification(const std::string& directoryPath);

    /**
     * Преобразовать момент времени одного типа в другой
     * @tparam TP Тип момента времени
     * @param tp Момент времени преобразующегося типа
     * @return Момент времени проеобразованного типа
     */
    template <typename TP>
    static std::time_t to_time_t(TP tp)
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
    static bool isFileUsageTimeExceeded();

    /**
     * Удалить файлы по сроку хранения
     */
    static void deleteFilesByRetentionPeriod();



    //Основные функции логирования (формирование сообщения)

    /**
     * Записать информацию в лог-файл
     * @param level Уровень логирования
     * @param message Ссылка на сообщение
     * @param exception Ссылка на исключение
     */
    static void log(Level level, const std::string& message, const std::exception& exception);

    /**
     * Сформировать сообщение для вывода
     * @param level Уровень логирования
     * @param message Сообщение
     * @param exception Исключение
     * @param timeEvent Текущее время
     * @return Сообщение для вывода
     */
    static std::string generateMessageForOutput(Level level, const std::string& message, const std::exception& exception, std::chrono::system_clock::time_point& timeEvent);

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
    static std::string timePointToString(const std::chrono::system_clock::time_point& timePoint);



    //Функции логирования в отдельном потоке (запись сообщения)

    /**
     * Записать информацию в файл и отправить информацию в монитор в отдельном потоке
     */
    void writeToFileAndMonitor();

    /**
     * Ожидать запуска монитора (другого процесса)
     */
    void waitForMonitorToStart();

    /**
     * Обработать очередь сообщений в отдельном потоке
     * @param messagesForOutput Ссылка на сообщение для вывода
     * @param monitorSender Ссылка на объект класса отправки сообщений для вывода на монитор
     */
    void processQueue(std::list<std::string> &messagesForOutput, MonitorSender& monitorSender);

    /**
     * Записать информацию в файл в отдельном потоке
     * @param messageForOutput Ссылка на сообщение для вывода
     */
    void writeToFile(const std::string& messageForOutput, MonitorSender& monitorSender);

    /**
     * Отправить информацию в монитор в отдельном потоке
     * @param messageForOutput Ссылка на сообщение для вывода
     * @param monitorSender Ссылка на объект класса отправки сообщений для вывода на монитор
     */
    void writeToMonitor(const std::string& messageForOutput, MonitorSender& monitorSender);



    //Вспомогательный класс

    /**
     * Класс реализует генерацию исключений-заглушек
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

};



#endif //SEARCH_ENGINE_LOGGER_H



