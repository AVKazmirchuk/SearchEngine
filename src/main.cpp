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
    unsigned int precision{6};
    //Ширина вывода
    unsigned int formatByWidth{2};
    //Желаемое количество потоков
    unsigned int desiredNumberOfThreads{11};
}



//Запустить расчёт релевантности
void runRelevanceCalculation()
{
    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(constants::configFilePath, constants::requestsFilePath, constants::answersFilePath, constants::precision, constants::formatByWidth, constants::desiredNumberOfThreads);

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();
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
        for (int i{1}; i < argc; i += 2)
        {
            if (std::strcmp(argv[i], "/c") == 0) constants::configFilePath = argv[i + 1];
            if (std::strcmp(argv[i], "/r") == 0) constants::requestsFilePath = argv[i + 1];
            if (std::strcmp(argv[i], "/a") == 0) constants::answersFilePath = argv[i + 1];
            if (std::strcmp(argv[i], "/l") == 0) constants::configLoggerFilePath = argv[i + 1];
            if (std::strcmp(argv[i], "/m") == 0) constants::configWriterMessageFilePath = argv[i + 1];

            unsigned int value;
            if (std::strcmp(argv[i], "/p") == 0) { std::stringstream ss{argv[i + 1]}; ss >> value; constants::precision = value;}
            if (std::strcmp(argv[i], "/f") == 0) { std::stringstream ss{argv[i + 1]}; ss >> value; constants::formatByWidth = value;}
            if (std::strcmp(argv[i], "/t") == 0) { std::stringstream ss{argv[i + 1]}; ss >> value; constants::desiredNumberOfThreads = value;}

            std::cout << argv[i] << " ";
        }

        //Создать объект логирования событий
        kav::Logger logger(constants::configLoggerFilePath, constants::configWriterMessageFilePath);

        try
        {
            //Вывести в лог запуск программы
            kav::Logger::info("Start SearchEngine");

            //Запустить саму программу
            runRelevanceCalculation();

            //Вывести в лог завершение программы
            kav::Logger::info("Stop SearchEngine");
        }
        catch (const std::exception& exception)
        {
            std::cout << exception.what() << std::endl;
            //Вывести сообщение о завершении работы программы
            std::cout << "Stop SearchEngine by error" << std::endl;

            //Выйти из программы по ошибке
            return EXIT_FAILURE;
        }


    }
    catch (const std::exception& exception)
    {
        std::cout << "Exception: " << exception.what() << std::endl;
        //Вывести сообщение о завершении работы программы
        std::cout << "Stop SearchEngine by error" << std::endl;

        //Выйти из программы по ошибке
        return EXIT_FAILURE;
    }

    //Выйти из программы по успеху
    return EXIT_SUCCESS;
}





