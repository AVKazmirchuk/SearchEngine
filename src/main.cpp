#include <iostream>
#include "searchEngine.h"
#include "kav/logger.h"

#include <fstream>

//Константы переменных
namespace constants
{

    //Путь файла конфигурации
    const std::string configFilePath{"config.json"};
    //Путь файла запросов
    const std::string requestsFilePath{"requests.json"};
    //Путь файла ответов
    const std::string answersFilePath{"answers.json"};
    //Путь файла конфигурации логирования
    const std::string configLoggerFilePath{"logger.json"};
    //Путь файла конфигурации очереди сообщений
    const std::string configWriterMessageFilePath{"messageQueue.json"};

    //Количество знаков после запятой
    const int precision{6};
    //Ширина вывода
    const int formatByWidth{2};
    //Желаемое количество потоков
    const unsigned int desiredNumberOfThreads{14};
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
        std::cout << exception.what() << std::endl;
        //Вывести сообщение о завершении работы программы
        std::cout << "Stop SearchEngine by error" << std::endl;

        //Выйти из программы по ошибке
        return EXIT_FAILURE;
    }

    //Выйти из программы по успеху
    return EXIT_SUCCESS;
}





