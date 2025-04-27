#include "searchEngine.h"
#include "general.h"



int main(int argc, char* argv[])
{
    //Защита от изменения имени файла (так как при инициализации очереди сообщений проверяется этот запущенный процесс)
    if (std::filesystem::path(argv[0]).filename() != "search_engine.exe")
    {
        //std::cout << argv[0] << std::endl;
        //std::cout << std::filesystem::path(argv[0]).filename();
        return -1;
    }

    MonitorSender monitorSender;

    //Инициализировать логирование (класс Logger)
    Logger::initialize(constants::configLoggerFilePath, &monitorSender);

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

    return 0;
}





