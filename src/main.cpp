#include <iostream>
#include "searchEngine.h"
#include "general.h"
#include "kav/logger.h"


//Вспомогательная функция запуска самой программы. Вынесено отдельно, для корректной обработки исключений
void auxiliary()
{
    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(constants::configFilePath, constants::requestsFilePath);

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

    //Создать объект класса логирования событий
    kav::Logger logger(constants::configLoggerFilePath, constants::configWriterMessageFilePath);

    //Вывести в лог запуск программы
    kav::Logger::info("Start SearchEngine");

    //Запустить саму программу
    try
    {
        auxiliary();
    }
    catch (const std::exception& exception)
    {
        //std::cout << '\n' << "from main in catch" << '\n' << std::endl;
        //kav::Logger::fatal("from auxiliary", exception);

        return EXIT_FAILURE;
    }

    //Вывести в лог завершение работы программы
    kav::Logger::info("Stop SearchEngine");

    return EXIT_SUCCESS;
}





