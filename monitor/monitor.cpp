//
// Created by Alexander on 20.04.2025.
//



#include <iostream>
#include <string>
#include <sstream>

#include "nlohmann/json.hpp"
#include "termcolor.h"

#include "monitor.h"
#include "../include/readWriteJSONFile.h"
#include "../include/general.h"


std::string determineLevel(const std::string& message)
{
    std::stringstream ss(message);
    std::string level;

    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');
    std::getline(ss, level, ' ');

    return level;
}

void outputToConsole(const std::string& message)
{
    //Определить уровень логирования
    std::string level{determineLevel(message)};

    //Вывести сообщение на монитор в своём цвете в соответствии уровню логирования
    if (level == "DEBUG:") std::cout << termcolor::grey << message << std::endl;
    else if (level == "INFO:") std::cout << termcolor::white << message << std::endl;
    else if (level == "WARNING:") std::cout << termcolor::yellow << message << std::endl;
    else if (level == "ERROR:") std::cout << termcolor::magenta << message << std::endl;
    else if (level == "FATAL:") std::cout << termcolor::red << message << std::endl;
}

void LoggerMonitor::initializeVariables(const JSON& configJSON)
{
    //Инициализировать переменные

    //Параметры основного процесса и монитора

    //Имя очереди
    nameOfQueue = configJSON["messageQueue"]["nameOfQueue"];
    //Максимальное количество сообщений в очереди
    maxNumberOfMessages = configJSON["messageQueue"]["maxNumberOfMessages"];
    //Максимальный размер сообщения
    maxMessageSize = configJSON["messageQueue"]["maxMessageSize"];
    //Имя файла основной программы
    fileNameOfMainProgram = configJSON["messageQueue"]["fileNameOfMainProgram"];
    //Имя файла монитора
    fileNameOfMonitor = configJSON["messageQueue"]["fileNameOfMonitor"];
    //Имя консоли
    nameOfConsole = configJSON["messageQueue"]["nameOfConsole"];
    //Признак запуска монитора
    indicatesMonitorStarting = configJSON["messageQueue"]["indicatesMonitorStarting"];

}

void LoggerMonitor::initialize(const std::string& configFilePath)
{
    //Создать JSON-объект конфигурации
    JSON configJSON = ReadWriteJSONFile::readJSONFile(configFilePath);

    //Инициализировать переменные
    initializeVariables(configJSON);
}