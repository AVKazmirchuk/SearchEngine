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



namespace kav
{
    //Класс хранения переменных шаблонов JSON-объектов файлов
    class TemplatesJSONObjects
    {

    public:

        TemplatesJSONObjects() = delete;

        /**
         * Прочитать шаблон JSON-объекта файла MessageQueue.json
         * @return Ссылка на переменную
         */
        static const JSON &configLoggerMonitorJSONTemplate()
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
 * Класс реализует вывод сообщений на консоль
 */
    class LoggerMonitor
    {

    public:

        /**
         * Создать объект классов СonfigLoggerMonitor и monitorReceiver
         * @param in_configLoggerMonitorFilePath Файл конфигурации монитора
         */
        explicit LoggerMonitor(const std::string &in_configLoggerMonitorFilePath)
                : configLoggerMonitor(in_configLoggerMonitorFilePath),
                  monitorReceiver(configLoggerMonitor.nameOfQueue(),
                                  configLoggerMonitor.maxNumberOfMessages(),
                                  configLoggerMonitor.maxMessageSize(),
                                  configLoggerMonitor.fileNameOfMainProgram())
        {
            //Добавить в контейнер имя очереди
            queuesInUse.push_back(configLoggerMonitor.nameOfQueue());

            //TODO Зачем поставил это условие - не помню
            if (queuesInUse.size() == 1)
            {
                //Зарегистрировать обработчик нажатия клавиш консоли
                SetConsoleCtrlHandler(&ConsoleCtrlEventHandler, TRUE);
            }
        }

        ~LoggerMonitor()
        {
            /*for (auto &queue: queuesInUse)
            {
                std::ofstream file{"LoggerMonitor.txt", std::ios::app};
                file << queue << std::endl;
            }*/
        }

        /**
         * Запустить монитор
         */
        void run();

    private:

        /**
             * Класс реализует чтение и хранение параметров для настройки классов LoggerMonitor, MonitorReceiver
             */
        class ConfigLoggerMonitor
        {

        public:

            /**
             * Создать и инициализировать объект класса ConfigLoggerMonitor
             * @param in_configLoggerMonitorFilePath Файл конфигурации монитора
             */
            explicit ConfigLoggerMonitor(const std::string &in_configLoggerMonitorFilePath)
                    : configLoggerMonitorFilePath{in_configLoggerMonitorFilePath}
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
             * Получить максимальное количество сообщений
             * @return Максимальное количество
             */
            [[nodiscard]] boost::interprocess::message_queue::size_type maxNumberOfMessages() const
            { return maxNumberOfMessagesValue; }

            /**
             * Получить максимальный размер сообщения
             * @return Максимальный размер
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
             * @return Признак запуска монитора
             */
            [[nodiscard]] const std::string &indicatesMonitorStarting() const
            { return indicatesMonitorStartingValue; }

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

        //Контейнер очередей сообщений
        inline static std::list<std::string> queuesInUse;

        /**
         * Вывод сообщения на консоль
         * @param message Ссылка на сообщение
         */
        void outputToConsole(const std::string &message);

        /**
         * Завершить работу. Используется в обработчике нажатия клавиш консоли
         */
        static void stop();

        /**
         * Обработчик нажатия клавиш консоли
         * @param dwCtrlType Событие нажатия сочетания клавиш или выключение или выход
         * @return Признак выполнения
         */
        static BOOL WINAPI ConsoleCtrlEventHandler(DWORD dwCtrlType);

    };

}

#endif //SEARCH_ENGINE_MONITOR_H
