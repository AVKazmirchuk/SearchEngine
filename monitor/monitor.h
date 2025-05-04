//
// Created by Alexander on 20.04.2025.
//

#ifndef SEARCH_ENGINE_MONITOR_H
#define SEARCH_ENGINE_MONITOR_H



#include <string>

#include "boost/interprocess/ipc/message_queue.hpp"
#include "nlohmann/json.hpp"

#include "../include/general.h"



//Определить уровень логирования
std::string determineLevel(const std::string& message);

//Вывести сообщение на консоль
void outputToConsole(const std::string& message);

/**
 * Класс логирования событий в монитор
 */
class LoggerMonitor
{

public:

    explicit LoggerMonitor(const std::string &configFilePath)
    {
        //Инициализировать (настроить) класс
        initialize(configFilePath);
    }

private:

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



};

#endif //SEARCH_ENGINE_MONITOR_H
