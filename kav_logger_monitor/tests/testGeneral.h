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
    static const std::string &messageDebug();

    /**
     * Прочитать сообщение
     * @return Ссылка на переменную
     */
    static const std::string &messageInfo();

    /**
     * Прочитать сообщение
     * @return Ссылка на переменную
     */
    static const std::string &messageWarning();

    /**
     * Прочитать сообщение
     * @return Ссылка на переменную
     */
    static const std::string &messageError();

    /**
     * Прочитать сообщение
     * @return Ссылка на переменную
     */
    static const std::string &messageFatal();

    /**
    * Прочитать сообщение
    * @return Ссылка на переменную
    */
    static const std::string &messageLogger();

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

    /**
     * Прочитать файл конфигурации монитора (отсутствует)
     * @return Ссылка на переменную
     */
    static const std::string &configLoggerMonitorFilePathNotExists();

    /**
     * Прочитать формат даты и времени
     * @return
     */
    static const std::string& dateTimeFormat();

    /**
     * Прочитать аттрибут (цвет) сообщения уровня Debug
     * @return Цвет
     */
    static unsigned short messageDebugColor();

    /**
     * Прочитать аттрибут (цвет) сообщения уровня Info
     * @return Цвет
     */
    static unsigned short messageInfoColor();

    /**
     * Прочитать аттрибут (цвет) сообщения уровня Warning
     * @return Цвет
     */
    static unsigned short messageWarningColor();

    /**
     * Прочитать аттрибут (цвет) сообщения уровня Error
     * @return Цвет
     */
    static unsigned short messageErrorColor();

    /**
     * Прочитать аттрибут (цвет) сообщения уровня Fatal
     * @return Цвет
     */
    static unsigned short messageFatalColor();

    /**
     * Прочитать аттрибут (цвет) сообщения уровня Logger
     * @return Цвет
     */
    static unsigned short messageLoggerColor();

};


//Получить строку из консоли
std::string getLineFromConsole(unsigned long x, unsigned long y, unsigned long length);

//Получить аттрибуты из консоли
std::vector<WORD> getAttributeFromConsole(unsigned long x, unsigned long y, unsigned long length);

//Получить размер консоли (количество столбцов и строк соответственно)
std::pair<unsigned long, unsigned long> getCursorPositionOfConsole();

//Получить номер строки консоли, содержащей отправленное сообщение
unsigned long getLineNumber(const std::string &message);

//Перевести отметку времени в строку
std::string timePointToString(const std::chrono::system_clock::time_point& now);



#endif //LOGGER_MONITOR_TESTGENERAL_H
