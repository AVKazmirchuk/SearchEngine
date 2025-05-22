//
// Created by Alexander on 20.04.2025.
//

#ifndef SEARCH_ENGINE_MONITOR_H
#define SEARCH_ENGINE_MONITOR_H



#include <list>
#include <string>
#include <fstream>

#include "boost/interprocess/ipc/message_queue.hpp"
#include "nlohmann/json.hpp"

#include "general.h"
#include "monitorReceiver.h"



/**
 * Класс логирования событий в монитор
 */
class LoggerMonitor
{

public:

    explicit LoggerMonitor(const std::string &in_configLoggerMonitorFilePath)
        : configLoggerMonitor(in_configLoggerMonitorFilePath),
          monitorReceiver(configLoggerMonitor.nameOfQueue(),
                          configLoggerMonitor.maxNumberOfMessages(),
                          configLoggerMonitor.maxMessageSize(),
                          configLoggerMonitor.fileNameOfMainProgram())
    {
        queuesInUse.push_back(configLoggerMonitor.nameOfQueue());

        if (queuesInUse.size() == 1)
        {
            SetConsoleCtrlHandler( &ConsoleCtrlEventHandler, TRUE );
        }
    }

    ~LoggerMonitor()
    {
        for (auto& queue : queuesInUse)
        {
            std::ofstream file{"LoggerMonitor.txt", std::ios::app};
            file << queue << std::endl;
        }
    }

    /**
     * Запустить монитор
     */
    void run();

private:

    /**
         * Класс реализует чтение и хранение параметров для настройки класса LoggerMonitor, MonitorReceiver
         */
    class ConfigLoggerMonitor
    {

    public:

        explicit ConfigLoggerMonitor(const std::string &in_configLoggerMonitorFilePath) : configLoggerMonitorFilePath{in_configLoggerMonitorFilePath}
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
        std::string configLoggerMonitorFilePath;
        //JSON-объект конфигурации логирования
        JSON configLoggerMonitorJSON;

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



    //Объект класса ConfigLoggerMonitor
    ConfigLoggerMonitor configLoggerMonitor;

    //Объект монитора получения сообщений
    MonitorReceiver monitorReceiver;

    //Контейнер очередей
    inline static std::list<std::string> queuesInUse;



    //Вывод сообщения на консоль
    void outputToConsole(const std::string& message);

    /**
     * Завершить работу
     */
    static void stop();

    static BOOL WINAPI ConsoleCtrlEventHandler( DWORD dwCtrlType );

};



#endif //SEARCH_ENGINE_MONITOR_H
