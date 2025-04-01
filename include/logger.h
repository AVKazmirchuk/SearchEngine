//
// Created by Alexander on 09.03.2025.
//

#ifndef SEARCH_ENGINE_LOGGER_H
#define SEARCH_ENGINE_LOGGER_H



#include <string>



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
    static void info(const std::string& message);
    
    /**
     * Записать сообщение уровня warning
     * @param message Сообщение
     */
    static void warn(const std::string& message);

    /**
     * Записать сообщение уровня error
     * @param message Сообщение
     */
    static void error(const std::string& message);

    /**
     * Записать сообщение уровня fatal
     * @param message Сообщение
     */
    static void fatal(const std::string& message);

};



#endif //SEARCH_ENGINE_LOGGER_H



