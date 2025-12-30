//
// Created by AKazmirchuk on 23.12.2025.
//



#include "programArguments.h"



bool ProcessProgramArguments::convertStringToNumber(const char *str, std::ptrdiff_t &value)
{
    //Создать объект потока для конвертации строки в число
    std::stringstream ss{str};

    //Если конвертация успешна и значение >= 0
    if (ss >> value && value >= 0)
    {
        //Условие удовлетворяет
        return true;
    }

    //Условие не удовлетворяет
    return false;
}

void ProcessProgramArguments::getHelp()
{
    std::cout << '\n' << "List of parameters:" << '\n';
    std::cout << '\t' << "/c    The path of the configuration file (config.json)" << '\n';
    std::cout << '\t' << "/r    Request file path (requests.json)" << '\n';
    std::cout << '\t' << "/a    The path of the response file (answers.json)" << '\n';
    std::cout << '\t' << "/dp   Create a database of documents or a database of document file paths (yes)" << '\n';
    std::cout << '\t' << "/l    The path of the logging configuration file (logger.json)" << '\n';
    std::cout << '\t' << "/m    The path of the message queue configuration file (messageQueue.json)" << '\n';
    std::cout << '\t' << "/lc   Log events to the console (yes)" << '\n';
    std::cout << '\t' << "/p    Number of decimal places (6)" << '\n';
    std::cout << '\t' << "/f    Output width (2)" << '\n';
    std::cout << '\t' << "/t    Desired number of threads (number of cores minus 2)" << '\n';
    std::cout << '\t' << "/e    Maximum number of unread files (0)" << '\n';
    std::cout << '\t' << "/?    Help" << '\n';
}

bool ProcessProgramArguments::processProgramArguments(int argc, char* argv[])
{
    //Если явные аргументы есть и вызывается справка
    if (argc > 1 && std::strcmp(argv[1], "/?") == 0)
    {
        //Получить справку
        getHelp();

        //Справка обработана
        return true;
    }

    //Для всех аргументов функции
    for (int i{1}; i < argc - 1; i += 2)
    {
        //Путь файла конфигурации
        if (std::strcmp(argv[i], "/c") == 0)
        {
            ProgramArguments::configFilePath() = argv[i + 1];

            continue;
        }
        //Путь файла запросов
        if (std::strcmp(argv[i], "/r") == 0)
        {
            ProgramArguments::requestsFilePath() = argv[i + 1];

            continue;
        }
        //Путь файла ответов
        if (std::strcmp(argv[i], "/a") == 0)
        {
            ProgramArguments::answersFilePath() = argv[i + 1];

            continue;
        }
        //Формировать базу документов или базу путей файлов документов
        if (std::strcmp(argv[i], "/dp") == 0)
        {
            ProgramArguments::documentsBaseOrPathsBase() = argv[i + 1];

            continue;
        }
        //Путь файла конфигурации логирования
        if (std::strcmp(argv[i], "/l") == 0)
        {
            ProgramArguments::configLoggerFilePath() = argv[i + 1];

            continue;
        }
        //Путь файла конфигурации очереди сообщений
        if (std::strcmp(argv[i], "/m") == 0)
        {
            ProgramArguments::configWriterMessageFilePath() = argv[i + 1];

            continue;
        }
        //Логировать события в консоль
        if (std::strcmp(argv[i], "/lc") == 0)
        {
            ProgramArguments::launchConsole() = argv[i + 1];

            continue;
        }

        //Подготовить переменную для конвертации
        std::ptrdiff_t value;

        //Количество знаков после запятой
        if (std::strcmp(argv[i], "/p") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value))
            {
                if (value >= 1 && value <= std::numeric_limits<std::remove_reference_t<decltype(ProgramArguments::precision())>>::max())
                {
                    ProgramArguments::precision() = value;
                }
            }

            continue;
        }
        //Ширина вывода
        if (std::strcmp(argv[i], "/f") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value))
            {
                if (value >= 0 && value <= std::numeric_limits<std::remove_reference_t<decltype(ProgramArguments::formatByWidth())>>::max())
                {
                    ProgramArguments::formatByWidth() = static_cast<std::remove_reference_t<decltype(ProgramArguments::formatByWidth())>>(value);
                }
            }

            continue;
        }
        //Желаемое количество потоков
        if (std::strcmp(argv[i], "/t") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value))
            {
                if (value >= 0 && value <= std::thread::hardware_concurrency())
                {
                    ProgramArguments::desiredNumberOfThreads() = value;
                }
            }

            continue;
        }
        //Максимальное количество непрочитанных файлов
        if (std::strcmp(argv[i], "/e") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value))
            {
                if (value >= 0 && value <= std::numeric_limits<std::remove_reference_t<decltype(ProgramArguments::maximumAllowableErrorsNumber())>>::max())
                {
                    ProgramArguments::maximumAllowableErrorsNumber() = value;
                }
            }

            continue;
        }
    }

    //Был вызван параметр отличный от справки
    return false;
}