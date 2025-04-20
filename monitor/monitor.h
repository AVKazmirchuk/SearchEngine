//
// Created by Alexander on 20.04.2025.
//

#ifndef SEARCH_ENGINE_MONITOR_H
#define SEARCH_ENGINE_MONITOR_H



#include <string>



//Определить уровень логирования
std::string determineLevel(const std::string& message);

//Вывести сообщение на консоль
void outputToConsole(const std::string& message);



#endif //SEARCH_ENGINE_MONITOR_H
