#include <iostream>
#include "searchEngine.h"
#include "kav/logger.h"



//Константы переменных
namespace constants
{

    //Путь файла конфигурации
    std::string configFilePath{"config.json"};
    //Путь файла запросов
    std::string requestsFilePath{"requests.json"};
    //Путь файла ответов
    std::string answersFilePath{"answers.json"};
    //Признак формирования базы документов или путей файлов документов
    std::string documentsBaseOrPathsBase{"yes"};
    //Путь файла конфигурации логирования
    std::string configLoggerFilePath{"logger.json"};
    //Путь файла конфигурации очереди сообщений
    std::string configWriterMessageFilePath{"messageQueue.json"};
    //Логировать события в консоль
    std::string launchConsole{"yes"};

    //Количество знаков после запятой
    unsigned int precision{6};
    //Ширина вывода
    unsigned int formatByWidth{2};
    //Желаемое количество потоков
    unsigned int desiredNumberOfThreads{std::thread::hardware_concurrency() - 2};
    //Максимальное количество непрочитанных файлов
    std::size_t maximumAllowableErrorsNumber{};
}

/**
 * Конвертировать строку в число
 * @param str Строка для конвертирования
 * @param value Получаемое значение после конвертации
 * @return Признак успешности конвертации
 */
bool convertStringToNumber(const char *str, std::size_t &value)
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

/*
 * Получить справку
 */
void getHelp()
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
    std::cout << '\t' << "/e    Maximum number of unread files (1)" << '\n';
    std::cout << '\t' << "/?    Help" << '\n';
}

/**
 * Обработать аргументы программы
 * @param argc Количество аргументов
 * @param argv Массив аргументов
 * @return Признак выбора справки
 */
bool processProgramArguments(int argc, char* argv[])
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
            constants::configFilePath = argv[i + 1];

            continue;
        }
        //Путь файла запросов
        if (std::strcmp(argv[i], "/r") == 0)
        {
            constants::requestsFilePath = argv[i + 1];

            continue;
        }
        //Путь файла ответов
        if (std::strcmp(argv[i], "/a") == 0)
        {
            constants::answersFilePath = argv[i + 1];

            continue;
        }
        //Aормировать базу документов или базу путей файлов документов
        if (std::strcmp(argv[i], "/dp") == 0)
        {
            constants::documentsBaseOrPathsBase = argv[i + 1];

            continue;
        }
        //Путь файла конфигурации логирования
        if (std::strcmp(argv[i], "/l") == 0)
        {
            constants::configLoggerFilePath = argv[i + 1];

            continue;
        }
        //Путь файла конфигурации очереди сообщений
        if (std::strcmp(argv[i], "/m") == 0)
        {
            constants::configWriterMessageFilePath = argv[i + 1];

            continue;
        }
        //Логировать события в консоль
        if (std::strcmp(argv[i], "/lc") == 0)
        {
            constants::launchConsole = argv[i + 1];

            continue;
        }

        //Подготовить переменную для конвертации
        std::size_t value;

        //Количество знаков после запятой
        if (std::strcmp(argv[i], "/p") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value)) constants::precision = value;

            continue;
        }
        //Ширина вывода
        if (std::strcmp(argv[i], "/f") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value)) constants::formatByWidth = value;

            continue;
        }
        //Желаемое количество потоков
        if (std::strcmp(argv[i], "/t") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value)) constants::desiredNumberOfThreads = value;

            continue;
        }
        //Максимальное количество непрочитанных файлов
        if (std::strcmp(argv[i], "/e") == 0)
        {
            if (convertStringToNumber(argv[i + 1], value)) constants::maximumAllowableErrorsNumber = value;

            continue;
        }
    }

    //Был вызван параметр отличный от справки
    return false;
}

/**
 * Запустить расчёт релевантности
 */
void runRelevanceCalculation()
{
    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(constants::configFilePath, constants::requestsFilePath, constants::answersFilePath, constants::documentsBaseOrPathsBase,
                              constants::precision,
                              constants::formatByWidth,
                              constants::desiredNumberOfThreads,
                              constants::maximumAllowableErrorsNumber);

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();
}

/**
 * Обработать исключения с логированием
 * @param exception Исключение
 */
void handleExceptionsWithLogging(const std::exception& exception)
{
    //Вывести в лог дополнительное сообщение
    kav::Logger::fatal("Early termination of the program!!!", exception);
    //Вывести в лог завершение программы
    kav::Logger::info("Stop SearchEngine");
}

/**
 * Обработать исключения без логирования
 * @param exception Исключение
 */
void handleExceptionsWithoutLogging(const std::exception& exception)
{
    //Вывести сообщение об исключении
    std::cout << "Exception: " << exception.what() << std::endl;
    //Вывести сообщение о завершении работы программы по ошибке
    std::cout << "Stop SearchEngine by error" << std::endl;
}

int main(int argc, char* argv[])
{
    //Защита от изменения имени файла (так как при инициализации очереди сообщений проверяется этот запущенный процесс)
    //Если имя файла отличное от указанного
    if (std::filesystem::path(argv[0]).filename() != "search_engine.exe")
    {
        //Выйти из программы по ошибке
        return EXIT_FAILURE;
    }

    try
    {
        //Если была вызвана справка
        if (processProgramArguments(argc, argv))
        {
            //Выйти из программы по успеху
            return EXIT_SUCCESS;
        }

        //Создать объект логирования событий
        kav::Logger logger(constants::configLoggerFilePath, constants::configWriterMessageFilePath, constants::launchConsole);

        try
        {
            //Вывести в лог запуск программы
            kav::Logger::info("Start SearchEngine");

            //Запустить расчёт релевантности
            runRelevanceCalculation();

            //Вывести в лог завершение программы
            kav::Logger::info("Stop SearchEngine");
        }
        //Обработать исключения выброшенные из класса Logger. Эти исключения уже нельзя логировать
        catch (const kav::LoggerException& exception)
        {
            //Обработать исключения без логирования
            handleExceptionsWithoutLogging(exception);

            //Выйти из программы по ошибке
            return EXIT_FAILURE;
        }
        //Обработать все исключения, кроме исключений выброшенных из класса Logger, которые можно логировать
        catch (const std::exception& exception)
        {
            //Обработать исключения с логированием
            handleExceptionsWithLogging(exception);

            //Выйти из программы по ошибке
            return EXIT_FAILURE;
        }
    }
    //Обработать исключения выброшенные из класса Logger и выше. Эти исключения уже нельзя логировать
    catch (const std::exception& exception)
    {
        //Обработать исключения без логирования
        handleExceptionsWithoutLogging(exception);

        //Выйти из программы по ошибке
        return EXIT_FAILURE;
    }

    //Выйти из программы по успеху
    return EXIT_SUCCESS;
}





