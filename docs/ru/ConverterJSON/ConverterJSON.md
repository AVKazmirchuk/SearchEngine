# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс ConverterJSON
Класс реализует работу с JSON-объектами.
### Выполняет следующие функции:
1. Получает список файлов документов.
2. Получает запросы.
3. Получает значение максимального количества ответов.
4. Записывает в JSON-объект результаты поиска.
5. Получает JSON-объект ответов.
6. Хранит JSON-объекты конфигурации, запросов, ответов.
7. Предоставляет ссылку на JSON-объект ответов.
### Конструкторы:
Инициализирует: ссылку на JSON-объект конфигурации, ссылку на JSON-объект запросов.
```cpp
 ConverterJSON(const JSON& in_configJSON, const JSON& in_requestsJSON)
     : configJSON(in_configJSON),
       requestsJSON(in_requestsJSON)
    {}
ConverterJSON(JSON&& in_configJSON, JSON&& in_requestsJSON)
    : configJSON(std::move(in_configJSON)),
      requestsJSON(std::move(in_requestsJSON))
    {}
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Получить список файлов документов:
```cpp
std::vector<std::string> getFilePaths();
```
Возвращаемое значение: Список файлов документов
#### Получить запросы:
```cpp
std::vector<std::string> getRequests();
```
#### Получить значение максимального количества ответов:
```cpp
int getMaxResponses();
```
#### Записать в JSON-объект результаты поиска:
```cpp
void setAnswersJSON(const std::vector<std::vector<std::pair<int, float>>>& answers, int maxResponses);
```
#### Получить JSON-объект ответов:
```cpp
JSON& getAnswersJSON();
```
### Примеры
```cpp
#include "converterJSON.h"

int main()
{
    //...
    //Создать/получить JSON-объекты конфигурации и запросов (configJSON, requestsJSON)
    //...

    //Создать объект класса ConverterJSON и инициализироать JSON-объектами конфигурации и запросов
    ConverterJSON converterJSONObj(configJSON, requestsJSON);

    //Получить список файлов документов
    std::vector<std::string> filePaths(converterJSONObj.getFilePaths());
    //Получить запросы
    std::vector<std::string> requests(converterJSONObj.getRequests());
    //Получить значение максимального количества ответов
    int maxResponses{converterJSONObj.getMaxResponses()};

    //...
    //Получить результаты поиска (answers)
    //...

    //Записать в JSON-объект результаты поиска
    converterJSONObj.setAnswersJSON(answers, maxResponses);
    //Получить JSON-объект ответов
    JSON& answersJSON{converterJSONObj.getAnswersJSON()};
}
```
