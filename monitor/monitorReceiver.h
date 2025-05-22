//
// Created by Alexander on 15.04.2025.
//

#ifndef SEARCH_ENGINE_MONITORRECEIVER_H
#define SEARCH_ENGINE_MONITORRECEIVER_H



#include "windows.h"
#include <tlhelp32.h>

#include "boost/interprocess/ipc/message_queue.hpp"







//Класс реализует получение сообщений для вывода на монитор
class MonitorReceiver
{

public:

    /**
     * Открыть или создать очередь сообщений.
     * Если процесс получения и вывода сообщений запущен, - значит очередь сообщений существует, - открыть очередь сообщений.
     * Если процесс получения и вывода сообщений не запущен, - значит очередь сообщений не существует, - создать очередь сообщений.
     */
    MonitorReceiver(const std::string& in_nameOfQueue,
                    const boost::interprocess::message_queue::size_type in_maxNumberOfMessages,
                    const boost::interprocess::message_queue::size_type in_maxMessageSize,
                    const std::string& in_fileNameOfMainProgram) :
            removeMessageQueue(in_nameOfQueue, in_fileNameOfMainProgram),
            mq{boost::interprocess::open_or_create, in_nameOfQueue.c_str(), in_maxNumberOfMessages, in_maxMessageSize}
            {}

    /**
     * Получить сообщение из очереди сообщений (ожидать сообщение)
     * @return Сообщение
     */
    std::string receive();

    /**
     * Получить константную ссылку на объект класса boost::interprocess::message_queue
     * @return Константная ссылка на объект класса boost::interprocess::message_queue
     */
    [[nodiscard]] const boost::interprocess::message_queue& get() const
    {
        return mq;
    }

    /**
     * Получить ссылку на объект класса boost::interprocess::message_queue
     * @return Ссылка на объект класса boost::interprocess::message_queue
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

        RemoveMessageQueue(const std::string& in_nameOfQueue, const std::string& in_fileNameOfMainProgram)
        {
            //Процесс получения и вывода сообщений не запущен
            if (!isProcessRun(in_fileNameOfMainProgram.c_str()))
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
        static bool isProcessRun(const char * processName);

    };

    RemoveMessageQueue removeMessageQueue;
    boost::interprocess::message_queue mq;

};



#endif //SEARCH_ENGINE_MONITORRECEIVER_H
