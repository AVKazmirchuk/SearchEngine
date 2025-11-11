#include <iostream>
#include "searchEngine.h"
#include "kav/logger.h"

#include <fstream>

//Константы переменных
namespace constants
{

    //Путь файла конфигурации
    std::string configFilePath{"config.json"};
    //Путь файла запросов
    std::string requestsFilePath{"requests.json"};
    //Путь файла ответов
    std::string answersFilePath{"answers.json"};
    //Путь файла конфигурации логирования
    std::string configLoggerFilePath{"logger.json"};
    //Путь файла конфигурации очереди сообщений
    std::string configWriterMessageFilePath{"messageQueue.json"};

    //Количество знаков после запятой
    int precision{6};
    //Ширина вывода
    int formatByWidth{2};
    //Желаемое количество потоков
    int desiredNumberOfThreads{static_cast<int>(std::thread::hardware_concurrency() - 2)};
    //Максимальное количество непрочитанных файлов
    int maximumAllowableErrorsNumber{1};
}

//Конвертировать строку в число
bool convertStringToNumber(char *str, int &value)
{
    std::stringstream ss{str};

    if (ss >> value && value >= 0) {return true;}

    return false;
}

//Обработать аргументы программы
void processProgramArguments(int argc, char* argv[])
{
    //Для всех аргументов функции
    for (int i{1}; i < argc; i += 2)
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

        //Подготовить переменную для конвертации
        int value;

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
}

//Запустить расчёт релевантности
void runRelevanceCalculation()
{
    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(constants::configFilePath, constants::requestsFilePath, constants::answersFilePath, constants::precision, constants::formatByWidth, constants::desiredNumberOfThreads, constants::maximumAllowableErrorsNumber);

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();
}

//Обработать исключения с логированием
void handleExceptionsWithLogging(const std::exception& exception)
{
    kav::Logger::fatal("Early termination of the program!!!", exception);

    //Вывести в лог завершение программы
    kav::Logger::info("Stop SearchEngine");
}

//Обработать исключения без логирования
void handleExceptionsWithoutLogging(const std::exception& exception)
{
    std::cout << "Exception: " << exception.what() << std::endl;
    //Вывести сообщение о завершении работы программы
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
        processProgramArguments(argc, argv);

        //Создать объект логирования событий
        kav::Logger logger(constants::configLoggerFilePath, constants::configWriterMessageFilePath);

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





