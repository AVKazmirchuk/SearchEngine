#include "searchEngine.h"
#include "general.h"



int main()
{
    //Проверить файл config.json
    checkFile(constants::configFilePath, constants::configTemplate);
    //Проверить файл requests.json
    checkFile(constants::requestsFilePath, constants::requestsTemplate);

    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(ReadWriteJSONFile().readJSONFile(constants::configFilePath),
                              ReadWriteJSONFile().readJSONFile(constants::requestsFilePath));

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    return 0;
}





