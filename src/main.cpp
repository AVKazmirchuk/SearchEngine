#include <iostream>
#include "searchEngine.h"
#include "general.h"



//Вспомогательная функция запуска самой программы. Вынесено отдельно, для корректной обработки исключений
void auxiliary()
{
    //Создать объект класса логирования событий
    Logger logger(constants::configLoggerFilePath, constants::configWriterMessageFilePath);

    //Вывести в лог запуск программы
    Logger::info("Start SearchEngine");

    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    //SearchEngine searchEngine(ReadWriteJSONFile::readJSONFile(constants::configFilePath, constants::configTemplate),
    //                          ReadWriteJSONFile::readJSONFile(constants::requestsFilePath, constants::requestsTemplate));

    SearchEngine searchEngine(constants::configFilePath, constants::requestsFilePath);

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //Вывести в лог завершение работы программы
    Logger::info("Stop SearchEngine");
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



/*    //Создать объект класса логирования событий
    Logger logger(constants::configLoggerFilePath, constants::configWriterMessageFilePath);

    //Вывести в лог запуск программы
    Logger::info("Start SearchEngine");

    //Проверить файл config.json
    checkFile(constants::configFilePath, constants::configTemplate);

    //Проверить файл requests.json
    checkFile(constants::requestsFilePath, constants::requestsTemplate);

    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(ReadWriteJSONFile::readJSONFile(constants::configFilePath),
                              ReadWriteJSONFile::readJSONFile(constants::requestsFilePath));

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //Вывести в лог завершение работы программы
    Logger::info("Stop SearchEngine");
*/

    //Запустить саму программу
    try
    {
        auxiliary();
    }
    catch (const std::exception& exception)
    {
        std::cout << exception.what();
    }

    return 0;
}





