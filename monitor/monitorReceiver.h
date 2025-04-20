//
// Created by Alexander on 15.04.2025.
//

#ifndef SEARCH_ENGINE_MONITORRECEIVER_H
#define SEARCH_ENGINE_MONITORRECEIVER_H



#include "boost/interprocess/ipc/message_queue.hpp"



class MonitorReceiver
{

public:

    /**
     * Открыть или создать очередь сообщений.
     * Если процесс получения и вывода сообщений запущен, - значит очередь сообщений существует, - открыть очередь сообщений.
     * Если процесс получения и вывода сообщений не запущен, - значит очередь сообщений не существует, - создать очередь сообщений.
     */
    MonitorReceiver() : mq{boost::interprocess::open_or_create, "search_engine", 100, 256} {}

    /**
     * Получить сообщение из очереди сообщений
     * @param message Сообщение
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

    boost::interprocess::message_queue mq;

};



#endif //SEARCH_ENGINE_MONITORRECEIVER_H
