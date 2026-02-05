//
// Created by AKazmirchuk on 05.02.2026.
//

#ifndef LOGGER_MONITOR_TESTGENERAL_H
#define LOGGER_MONITOR_TESTGENERAL_H



#include "monitor.h"
#include "monitorReceiver.h"
#include "monitorSender.h"



/**
 * Класс хранения переменных аргументов программы
 */
class ProgramArguments
{

public:

    ProgramArguments() = delete;

    /**
     * Прочитать имя очереди
     * @return Ссылка на переменную
     */
    static const std::string &nameOfQueue();

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
     * Прочитать сообщение
     * @return Ссылка на переменную
     */
    static const std::string &message();

    /**
     * Прочитать сообщение об остановке программы
     * @return Ссылка на переменную
     */
    static const std::string& messageStop();

    /**
     * Прочитать файл конфигурации монитора
     * @return Ссылка на переменную
     */
    static const std::string &configLoggerMonitorFilePath();

};

#endif //LOGGER_MONITOR_TESTGENERAL_H
