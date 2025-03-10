//
// Created by Alexander on 09.03.2025.
//

#ifndef SEARCH_ENGINE_LOGGER_H
#define SEARCH_ENGINE_LOGGER_H



#include <iostream>



/**
 * Класс реализует логирование событий
 */
class Logger
{

public:

    Logger() = default;

    /**
     * Записать сообщение уровня information
     * @param message Сообщение
     */
    void info(const std::string& message);
    
    /**
     * Записать сообщение уровня warning
     * @param message Сообщение
     */
    void warn(const std::string& message);

    /**
     * Записать сообщение уровня error
     * @param message Сообщение
     */
    void error(const std::string& message);

    /**
     * Записать сообщение уровня fatal
     * @param message Сообщение
     */
    void fatal(const std::string& message);

};



#endif //SEARCH_ENGINE_LOGGER_H



