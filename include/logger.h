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

//void writeToFileAndMonitor();
//void writeToMonitor();
//void writeToFile();

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

    Logger()
    {
        if (self != nullptr) throw std::runtime_error("It is impossible to create an object!");

        self = this;

        startThread = std::async(&Logger::writeToFileAndMonitor, this);

        if (!isProcessRun("search_engine_monitor.exe"))
        {
            std::filesystem::remove(R"(C:\Windows\Temp\search_engine_monitor)");

            //Запустить процесс получения и вывода сообщений (в любом случае). Этот процесс может быть запущен только в одном экземпляре
            // (регулируется именованным мьютексом).
            startMonitor(
                    R"(C:\\Users\\Alexander\\CLionProjects\\search_engine\\cmake-build-release\\monitor\\search_engine_monitor.exe)");

            std::size_t numLoop{};
            do
            {
                //std::this_thread::sleep_for(std::chrono::milliseconds(1));
                ++numLoop;
            } while (!std::filesystem::exists(R"(C:\Windows\Temp\search_engine_monitor)"));

            std::cout << numLoop << std::endl;
        }

        initialize(constants::configLoggerFilePath);

        //startThread = std::async(&Logger::writeToFileAndMonitor, this);


    }

    ~Logger()
    {
        stopProgram.store(true);

        pushMessage.store(false);
        cvPushMessage.notify_one();

        //std::unique_lock<std::mutex> uniqueLock(mutThreadStop);
        //cvThreadStop.wait(uniqueLock, [this]() { return threadStop.load(); });

        startThread.wait();
    }

    /**
     * Инициализировать (настроить) класс
     */
    static void initialize(const std::string& configFilePath);

    static std::filesystem::path& getFile()
    {
        return file;
    }

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

    inline static Logger *self{};

    //friend void writeToFileAndMonitor();
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

    //Отдельный поток записи информации в файл и в монитор
    inline static std::thread threadOfWriteToFileAndMonitor;

    inline static std::string messageToForward{};

    std::mutex mutContainerOfMessages;
    std::mutex mutThreadStop;

    std::future<void> startThread;

    std::condition_variable cvPushMessage;
    std::atomic<bool> pushMessage{false};

    std::condition_variable cvStopProgram;
    std::atomic<bool> stopProgram{false};

    std::atomic<bool> threadStop{false};
    std::condition_variable cvThreadStop;

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
     * Получить файл для записи
     * @param directoryPath Путь к директории с логами
     */
    static void getFile(const std::string& directoryPath);

    /**
     * Удалить файлы по сроку хранения
     */
    static void deleteFilesByRetentionPeriod();

    /**
     * Перевести время создания файла в строку
     * @param timePoint Текущее время
     * @return Строка времени создания файла
     */
    static std::string timePointToString(const std::chrono::system_clock::time_point& timePoint);

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
     * Получить новый файл
     * @return Путь нового файла
     */
    static std::filesystem::path getNewFile();

    /**
     * Определить, превышено ли  время использования файла
     * @return
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
     * @param directoryPath Путь к директории с логами
     * @return
     */
    static void identifyFilesByLastModification(const std::string& directoryPath);

    /**
     * Записать информацию в файл
     * @param messageForOutput Сообщение для вывода
     */
    void writeToFile(const std::string& messageForOutput);

    /**
     * Отправить информацию в монитор
     * @param messageForOutput Сообщение для вывода
     */
    void writeToMonitor(const std::string& messageForOutput, MonitorSender& monitorSender);

    /**
     * Записать информацию в файл и отправить информацию в монитор
     */
    void writeToFileAndMonitor();

    /**
     * Записать информацию в лог-файл
     * @param level Уровень логирования
     * @param message Сообщение
     * @param exception Исключение
     */
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
    //static void startMonitor(LPCSTR lpApplicationName);

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



