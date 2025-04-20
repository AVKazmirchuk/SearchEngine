//
// Created by Alexander on 09.03.2025.
//

#ifndef SEARCH_ENGINE_LOGGER_H
#define SEARCH_ENGINE_LOGGER_H



#include <string>
#include <filesystem>
#include <vector>

#include "checkFileException.h"
#include "general.h"
#include "monitorSender.h"



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

    /**
     * Инициализировать (настроить) класс
     */
    static void initialize(const std::string& configFilePath);

    /**
     * Записать сообщение уровня debug
     * @param message Сообщение
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

    //Типы интервалов времени
    using Seconds = std::chrono::duration<int64_t, std::ratio<1>>;
    using Minutes = std::chrono::duration<int64_t, std::ratio<60>>;
    using Hours = std::chrono::duration<int64_t, std::ratio<60*60>>;
    using Days = std::chrono::duration<int64_t, std::ratio<60*60*24>>;
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

    //Формат даты и времени записи в файл
    static inline std::string dateTimeFormat{};
    //Формат имени файла
    static inline std::string fileNameFormat{};
    //Предельный размер файла
    static inline  uint64_t fileSizeLimit{};
    //Директория с файлами
    static inline std::string filesDirectory{};

    //Файл для записи
    static inline std::filesystem::path file{};

    static inline bool isFileForWriteOpen{};

    //Контейнер пар пути и момента времени последнего изменения файла
    inline static std::vector<std::pair<std::filesystem::path, std::chrono::system_clock::time_point>> logs{};

    //Объект монитора отправки сообщений
    inline static MonitorSender monitorSender{};

    /**
     * Инициализировать переменные
     * @param configJSON JSON-объект содержащий значения
     */
    static void initializeVariables(const JSON& configJSON);

    /**
     * Настроить класс
     */
    static void setupClass();

    /**
     * Определить необходимость удалить очередь
     */
    static void shouldDeleteMessageQueue();

    /**
     * Получить файл для записи
     * @param directoryPath
     * @return Путь файла для записи
     */
    static void getFile(const std::string& directoryPath);

    /**
     * Удалить файлы по сроку хранения
     */
    static void deleteFilesByRetentionPeriod();

    /**
     * Перевести время создания файла в строку
     * @param timePoint
     * @return Строка времени создания файла
     */
    static std::string timePointToString(const std::chrono::system_clock::time_point& timePoint);

    /**
     * Получить новый файл
     * @return Путь нового файла
     */
    static std::filesystem::path getNewFile();

    /**
     * Определить, превышено ли  время использования файла
     */
    static bool isFileUsageTimeExceeded();

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
     * Определить файлы по последнему изменению
     * @param directoryPath
     * @return
     */
    static void identifyFilesByLastModification(const std::string& directoryPath);

    //Записать информацию в лог-файл
    static void log(Level level, const std::string& message, const std::exception& exception);

    /**
     * Получить из уровня логирования строку
     * @param level Уровень логирования
     * @return Строка
     */
    static std::string levelToString(Level level);

    /**
     * Запустить независимый процесс получения и вывода сообщений
     * @param lpApplicationName Имя процесса
     */
    static void startMonitor(LPCSTR lpApplicationName);

   /**
    * Определить, запущен ли процесс
    * @param processName Имя процесса
    * @return Процесс запущен (true)/не запущен (false)
    */
    static bool isProcessRun(const char * processName);

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



