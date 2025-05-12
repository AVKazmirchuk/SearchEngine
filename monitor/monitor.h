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



/**
 * Класс логирования событий в монитор
 */
class LoggerMonitor
{

public:

    explicit LoggerMonitor(const std::string &in_configMessageQueueFilePath)
        : configMessageQueueFilePath{in_configMessageQueueFilePath}
    {
        //Инициализировать (настроить) класс
        initialize();
    }

    ~LoggerMonitor()
    {
        std::ofstream file{"LoggerMonitor", std::ios::app};
        file << "LoggerMonitor shutdown!";
    }

    /**
     * Запустить монитор
     */
    void run();

    /**
     * Завершить работу
     */
    static void stop();

private:

    //Путь файла конфигурации очереди сообщений
    std::string configMessageQueueFilePath;

    inline static std::list<std::string> queuesInUse;

    //Параметры основного процесса и монитора

    //Имя очереди
    std::string nameOfQueue{};
    //Максимальное количество сообщений в очереди
    boost::interprocess::message_queue::size_type maxNumberOfMessages{};
    //Максимальный размер сообщения
    boost::interprocess::message_queue::size_type maxMessageSize{};
    //Имя файла основной программы
    std::string fileNameOfMainProgram{};
    //Имя файла монитора
    std::string fileNameOfMonitor{};
    //Имя консоли
    std::string nameOfConsole{};
    //Признак запуска монитора
    std::string indicatesMonitorStarting{};

    /**
     * Инициализировать (настроить) класс
     * @param configFilePath Ссылка на файл конфигурации логирования
     */
    void initialize();

    /**
     * Инициализировать переменные
     * @param configJSON JSON-объект содержащий значения
     */
    void initializeVariables(const JSON& configJSON);

    //Вывод сообщения на консоль
    void outputToConsole(const std::string& message);

};

#endif //SEARCH_ENGINE_MONITOR_H
