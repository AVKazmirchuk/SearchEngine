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

    /**
     * Завершить работу
     */
    static void stop();

    static BOOL WINAPI ConsoleCtrlEventHandler( DWORD dwCtrlType )
    {
        switch (dwCtrlType)
        {
            case CTRL_C_EVENT:
            case CTRL_BREAK_EVENT:
                // Do nothing.
                // To prevent other potential handlers from
                // doing anything, return TRUE instead.
                //return FALSE;

            case CTRL_CLOSE_EVENT:
                // Do your final processing here!
                LoggerMonitor::stop();

                std::this_thread::sleep_for(std::chrono::seconds(15));

                return TRUE;

            case CTRL_LOGOFF_EVENT:
            case CTRL_SHUTDOWN_EVENT:
                // Please be careful to read the implications of using
                // each one of these, and the applicability to your
                // code. Unless you are writing a Windows Service,
                // chances are you only need to pay attention to the
                // CTRL_CLOSE_EVENT type.
                return FALSE;
        }

        // If it gets this far (it shouldn't), do nothing.
        return FALSE;
    }


};

#endif //SEARCH_ENGINE_MONITOR_H
