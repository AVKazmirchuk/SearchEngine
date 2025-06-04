//
// Created by Alexander on 15.04.2025.
//

#ifndef SEARCH_ENGINE_MONITORSENDER_H
#define SEARCH_ENGINE_MONITORSENDER_H



#include "windows.h"
#include <tlhelp32.h>

#include "boost/interprocess/ipc/message_queue.hpp"



//Класс отправки сообщений для вывода на монитор
class MonitorSender
{

public:

    /**
     * Открыть или создать очередь сообщений.
     * Если процесс получения и вывода сообщений запущен, - значит очередь сообщений существует, - открыть очередь сообщений.
     * Если процесс получения и вывода сообщений не запущен, - значит очередь сообщений не существует, - создать очередь сообщений.
     */
    MonitorSender(const std::string& in_nameOfQueue,
                  const boost::interprocess::message_queue::size_type in_maxNumberOfMessages,
                  const boost::interprocess::message_queue::size_type in_maxMessageSize,
                  const std::string& in_fileNameOfMonitor) :
    removeMessageQueue(in_nameOfQueue, in_fileNameOfMonitor),
    mq(boost::interprocess::open_or_create, in_nameOfQueue.c_str(), in_maxNumberOfMessages, in_maxMessageSize)
    {

    }

    /**
     * Отправить сообщение в очередь сообщений
     * @param message Ссылка на сообщение
     */
    void send(const std::string& message);

    /**
     * Получить объект класса boost::interprocess::message_queue
     * @return Константная ссылка на объект boost::interprocess::message_queue
     */
    [[nodiscard]] const boost::interprocess::message_queue& get() const
    {
        return mq;
    }

    /**
     * Получить объект класса boost::interprocess::message_queue
     * @return Ссылка на объект boost::interprocess::message_queue
     */
    boost::interprocess::message_queue& get()
    {
        return mq;
    }

private:

    //Вспомогательный класс для удаления оставшейся очереди сообщений (во избежание ошибок) перед инициализацией очереди
    class RemoveMessageQueue
    {

    public:

        RemoveMessageQueue(const std::string& in_nameOfQueue, const std::string& in_fileNameOfMonitor)
        {
            //Процесс получения и вывода сообщений не запущен
            if (!isProcessRun(in_fileNameOfMonitor.c_str()))
            {
                //Удалить оставшуюся очередь (скорее всего, заблокированную)
                boost::interprocess::message_queue::remove(in_nameOfQueue.c_str());

            }
        }

    private:

        /**
         * Определить, запущен ли процесс
         * @param processName Имя процесса
         * @return Процесс запущен (true)/не запущен (false)
         */
        bool isProcessRun(const char * processName);

    };

    RemoveMessageQueue removeMessageQueue;
    boost::interprocess::message_queue mq;

};



#endif //SEARCH_ENGINE_MONITORSENDER_H
