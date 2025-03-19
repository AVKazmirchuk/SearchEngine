# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс ConverterJSON
Класс реализует работу с JSON-объектами.
### Выполняет следующие функции:
1. Получает и хранит JSON-объект конфигурации.
2. Получает и хранит JSON-объект запросов.
3. Читает список файлов документов и предоставляет его.
4. Читает из JSON-объекта конфигурациии имя программы, версию и максимальное количество ответов, и использует их.
5. Читает запросы из JSON-объекта запросов.
6. Записывает в JSON-объект оветов результаты поиска.
7. Хранит JSON-объекты конфигурации, запросов, ответов.
8. Предоставляет ссылку на JSON-объект ответов.
### Файлы конфигурации, запросов и ответов
Программа использует файлы конфигурации и запросов (config.json и requests.json). По результатам поиска в документах по запросам формируется файл answers.json, находящийся по этому же пути. Эти файлы находятся вместе с программой.\
Файл config.json:
```json
{
  "config": {
    "name": "SkillboxSearchEngine",
    "version": "0.1",
    "max_responses": 5
  },
  "files": [
    "../../resources/file001.txt",
    "../../resources/file002.txt",
    "../../resources/file003.txt"
  ]
}
```
Назначение полей:
- config: общая информация
- name: имя программы
- version: версия программы
- max_responses: максимальное количество ответов на один запрос
- files: пути к файлам документов, по которым необходимо осуществить поиск

Файл requests.json:
```json
{
  "requests": [
    "of the and water is year",
    "water another good see",
    "music"
  ]
}
```
Назначение полей:
- requests: список запросов; по ним будет вестись поиск в документах.

Файл answers.json:
```json
{
  "answers": {
    "request001": {
      "result": "true",
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 2,
          "rank": 0.94737
        }
      ]
    },
    "request002": {
      "result": "true",
        "docid": 0,
        "rank": 0.03509
      },
    "request003": {
      "result": "false"
    }
  }
}
```
Назначение полей:
- answers: базовое поле
- request001...003: идентификатор запроса
- result: результат поиска (найден ли хотя бы один документ, подходящий по запросу)
- relevance: присутствует, если на запрос найдено более одного документа
- docid: идентификатор документа
- rank: поисковый рейтинг

### Конструкторы:
Инициализирует: ссылку на JSON-объект конфигурации, ссылку на JSON-объект запросов.
```cpp
 ConverterJSON(const JSON& in_configJSON, const JSON& in_requestsJSON)
     : configJSON(in_configJSON),
       requestsJSON(in_requestsJSON)

ConverterJSON(JSON&& in_configJSON, JSON&& in_requestsJSON)
    : configJSON(std::move(in_configJSON)),
      requestsJSON(std::move(in_requestsJSON))

```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### О программе
```cpp
std::string about();
```
Возвращаемое значение: строка о программе (название, версия)
#### Получить список файлов документов:
```cpp
std::vector<std::string> getFilePaths();
```
Возвращаемое значение: список файлов документов
#### Получить запросы:
```cpp
std::vector<std::string> getRequests();
```
Возвращаемое значение: запросы
#### Получить значение максимального количества ответов:
```cpp
int getMaxResponses();
```
Возвращаемое значение: максимальное количество ответов
#### Записать в JSON-объект результаты поиска:
```cpp
void setAnswersJSON(const std::vector<std::vector<std::pair<int, float>>>& answers, int maxResponses);
```
Параметры: база релевантности ответов, максимальное количество ответов
#### Получить JSON-объект ответов:
```cpp
JSON& getAnswersJSON();
```
Возвращаемое значение: ссылка на JSON-объект ответов
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
