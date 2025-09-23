#include <iostream>
#include "searchEngine.h"
#include "general.h"
#include "kav/logger.h"



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

}



//Вспомогательная функция запуска самой программы. Вынесено отдельно, для корректной обработки исключений
void auxiliary()
{
    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(constants::configFilePath, constants::requestsFilePath, constants::answersFilePath, constants::precision, constants::formatByWidth);

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();
}

int main(int argc, char* argv[])
{
    //Защита от изменения имени файла (так как при инициализации очереди сообщений проверяется этот запущенный процесс)
    if (std::filesystem::path(argv[0]).filename() != "search_engine.exe")
    {
        //std::cout << argv[0] << std::endl;
        //std::cout << std::filesystem::path(argv[0]).filename();
        return -1;
    }

    try
    {
        //Создать объект класса логирования событий
        kav::Logger logger(constants::configLoggerFilePath, constants::configWriterMessageFilePath);

        try
        {
            //Вывести в лог запуск программы
            kav::Logger::info("Start SearchEngine");

            //Запустить саму программу
            auxiliary();

            //Вывести в лог завершение программы
            kav::Logger::info("Stop SearchEngine");
        }
        catch (const std::exception& exception)
        {
            //std::cout << '\n' << "from main in catch" << '\n' << std::endl;
            //kav::Logger::fatal("from auxiliary", exception);

            //Вывести в лог завершение работы программы
            kav::Logger::info("Stop SearchEngine");

            return EXIT_FAILURE;
        }


    }
    catch (const kav::LoggerException& exception)
    {
        std::cout << exception.what() << std::endl;
        //Вывести сообщение о завершении работы программы
        std::cout << "Stop SearchEngine" << std::endl;

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}





