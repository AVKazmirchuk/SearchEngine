//
// Created by AKazmirchuk on 23.12.2025.
//

#ifndef SEARCH_ENGINE_SOLUTION_PROGRAMARGUMENTS_H
#define SEARCH_ENGINE_SOLUTION_PROGRAMARGUMENTS_H



#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>

#include "constants.h"



/**
 * Класс хранения переменных аргументов программы
 */
class ProgramArguments
{

public:

    ProgramArguments() = delete;

    /**
     * Прочитать/записать путь файла конфигурации
     * @return Ссылка на переменную
     */
    static std::string& configFilePath()
    {
        //Значение по умолчанию
        static std::string variable{"config.json"};
        return variable;
    }

    /**
     * Прочитать/записать путь файла запросов
     * @return Ссылка на переменную
     */
    static std::string& requestsFilePath()
    {
        //Значение по умолчанию
        static std::string variable{"requests.json"};
        return variable;
    }

    /**
     * Прочитать/записать путь файла ответов
     * @return Ссылка на переменную
     */
    static std::string& answersFilePath()
    {
        //Значение по умолчанию
        static std::string variable{"answers.json"};
        return variable;
    }

    /**
     * Прочитать/записать признак формирования базы документов или путей файлов документов
     * @return Ссылка на переменную
     */
    static std::string& documentsBaseOrPathsBase()
    {
        //Значение по умолчанию
        static std::string variable{Constants::default_documentsBaseOrPathsBase()};
        return variable;
    }

    /**
     * Прочитать/записать путь файла конфигурации логирования
     * @return Ссылка на переменную
     */
    static std::string& configLoggerFilePath()
    {
        //Значение по умолчанию
        static std::string variable{"logger.json"};
        return variable;
    }

    /**
     * Прочитать/записать путь файла конфигурации очереди сообщений
     * @return Ссылка на переменную
     */
    static std::string& configWriterMessageFilePath()
    {
        //Значение по умолчанию
        static std::string variable{"messageQueue.json"};
        return variable;
    }

    /**
     * Прочитать/записать признак логирования событий в консоль
     * @return Ссылка на переменную
     */
    static std::string& launchConsole()
    {
        //Значение по умолчанию
        static std::string variable{Constants::default_launchConsole()};
        return variable;
    }

    /**
     * Прочитать/записать количество знаков после запятой
     * @return Ссылка на переменную
     */
    static unsigned int& precision()
    {
        //Значение по умолчанию
        static unsigned int variable{6};
        return variable;
    }

    /**
     * Прочитать/записать ширину вывода
     * @return Ссылка на переменную
     */
    static int& formatByWidth()
    {
        //Значение по умолчанию
        static int variable{2};
        return variable;
    }

    /**
     * Прочитать/записать желаемое количество потоков
     * @return Ссылка на переменную
     */
    static unsigned int& desiredNumberOfThreads()
    {
        //Значение по умолчанию
        static unsigned int variable{std::thread::hardware_concurrency() - 1};
        return variable;
    }

    /**
     * Прочитать/записать максимальное количество непрочитанных файлов
     * @return Ссылка на переменную
     */
    static std::size_t& maximumAllowableErrorsNumber()
    {
        //Значение по умолчанию
        static std::size_t variable{0};
        return variable;
    }

};//*/

/**
 * Класс реализует обработку аргументов программы
 */
class ProcessProgramArguments
{

public:

    ProcessProgramArguments() = delete;

    /**
     * Обработать аргументы программы
     * @param argc Количество аргументов
     * @param argv Массив аргументов
     * @return Признак выбора справки
     */
    static bool processProgramArguments(int argc, char* argv[]);

private:

    /**
     * Конвертировать строку в число
     * @param str Строка для конвертирования
     * @param value Получаемое значение после конвертации
     * @return Признак успешности конвертации
     */
    static bool convertStringToNumber(const char *str, std::ptrdiff_t &value);

    /*
     * Получить справку
     */
    static void getHelp();

};

#ifdef PROGRAM_ARGUMENTS
//Класс хранения переменных аргументов программы
class ProgramArguments
{

public:

    ProgramArguments() = delete;

    /**
     * Прочитать путь файла конфигурации
     * @return Переменная
     */
    static std::string get_configFilePath()
    {
        //Значение по умолчанию
        std::string default_configFilePath{"config.json"};
        //Если переменная имеет значение по умолчанию - определить его
        if (!assigned_configFilePath) configFilePath = default_configFilePath;
        //Вернуть переменную
        return configFilePath;
    }

    /**
     * Записать путь файла конфигурации. Можно сделать проверку на допустимые значения (вернуть признак)
     * @param in_configFilePath Переменная
     */
    static void set_configFilePath(const std::string &in_configFilePath)
    {
        //Записать переменную
        configFilePath = in_configFilePath;
        //Поставить признак изменения переменной
        assigned_configFilePath = true;
    }

private:

    //Переменная
    inline static std::string configFilePath;
    //Признак изменения переменной
    inline static bool assigned_configFilePath{};

};
#endif //PROGRAM_ARGUMENTS



#endif //SEARCH_ENGINE_SOLUTION_PROGRAMARGUMENTS_H
