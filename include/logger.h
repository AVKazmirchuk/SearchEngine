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

    void info(const std::string& message);

    void warn(const std::string& message);

    void error(const std::string& message);

    void fatal(const std::string& message);

};



#endif //SEARCH_ENGINE_LOGGER_H



