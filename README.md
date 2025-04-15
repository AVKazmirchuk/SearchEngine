# SearchEngine

Программа осушествляет поиск в документах по запросам и выдаёт релевантные ответы.

## Описание

В организациях бывает потребность поиска информации по базе документов. Программе указываются в файлах JSON пути документов и запросы. По документам строится база инвертированного индекса, на основе которого определяется релевантность ответа (содержимого документа) для каждого запроса. По завершении поиска результаты выводятся в файл JSON, где для каждого запроса указан документ со степенью релевантности.\
\
В проекте использована многопоточная обработка (использована стандартная библиотека), - где необходимо. Использована сторонняя библиотека для работы с форматом JSON - [nlohmann/json](https://github.com/nlohmann/json/blob/develop/README.md). Использована сторонняя библиотека для межпроцессного обмена данными с помощью очереди сообщений - [boost/interprocess/ipc/message_queue](https://www.boost.org/doc/libs/master/doc/html/interprocess/synchronization_mechanisms.html#interprocess.synchronization_mechanisms.message_queue).
Проект может быть использован в виде готовой программы (консольного типа) или как библиотека. Архитектура и подробное описание классов приводится в [документации](./docs/ru/index.md).

## Зависимости

Программа была разработана и протестирована на С++ версии 17. Целевые ОС использования MS Windows 10, MS Windows 11. Для интеграции библиотек в проект можно воспользоваться следующими ссылками:
- библиотека [nlohmann/json](https://github.com/nlohmann/json/#integration) для работы с JSON-форматом;
- библиотека  [boost/interprocess/ipc/message_queue](https://www.boost.org/doc/libs/1_88_0/more/getting_started/windows.html)

Для запуска программы не требуется устанавливать дополнительные компоненты. Программа скомпилирована с необходимыми статическими библиотеками. 

## Установка

&emsp;Для использования проекта можно склонировать репозиторий или вручную добавить компоненты.\
&emsp;Все необходимые файлы (заголовочные и реализации) находятся в директориях "include", "monitor", "nlohmann_json", "resources", "src", "tests". Файлы CMake находятся в корне репозитория и в директории "src". В директории "monitor" находятся файлы реализации отдельной программы "search_engine_monitor" и CMake. В директории "tests" находятся файлы реализации тестов и CMake. Также необходимо скопировать файлы config.json и requests.json (конфигурации и запросов), и файл "logger.json", из репозитория директории "resources" в директорию с исполняемым файлом проекта search-engine.exe. Также необходимо скопировать файл "search_engine_monitor.exe" из директории проекта в директорию с исполняемым файлом проекта search-engine.exe.\
&emsp;Чтобы использовать проект как библиотеку небходимо подключить библиотеку [nlohmann/json](https://github.com/nlohmann/json/#integration) (в проекте это уже сделано) и отдельно скопировать файлы указанные выше.\
&emsp;Чтобы использовать проект как готовую программу, можно скачать релиз или скомпилировать из своего проекта. Обратите внимание, что необходимо так же скопировать файлы config.json и requests.json (конфигурации и запросов) из репозитория директории "resources" в директорию с исполняемым файлом search-engine.exe.\
&emsp;Так же для быстрого использования-тестирования программы, без каких-либо правок файла config.json, можно скопировать директорию "resources" из репозитория директории "resources" в директорию с исполняемым файлом search-engine.exe. В директории "resources" находятся три документа для примера, по которым осуществляется поиск.\
&emsp;То есть, в любом случае вы получаете начальную готовую структуру для немедленного применения.

## Как использовать проект

Программа использует файлы конфигурации и запросов (config.json и requests.json). По результатам поиска в документах по запросам формируется файл answers.json, находящийся по этому же пути.\
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
В поле "files" прописываются пути до файлов документов. В поле "max_responses" указывается максимальное количество ответов (количество документов для каждого запроса). Назначение других полей очевидно.
\
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
В поле "requests" прописываются сами запросы; по ним будет вестись поиск в документах.\
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
В этом файле для каждого запроса приводятся ID документов со значением релевантности ответа.

### Программа

Для запуска программы надо просто запустить файл search_engine.exe без ключей.\
Для работы необходимо, чтобы файлы конфигурации и запросов (config.json и requests.json) находились в директории с программой. В этой же директории по окончании поиска будет создан файл ответов (answers.json).

### Библиотека

Для использования в самой программе (в функции main) необходимо оперировать объектом класса SearchEngine. Он уже в свою очередь управляет взаимодействием между другими классами.\
Есть следующие функции рассчёта релевантности:
1. Рассчитать релевантность ответов (изменяются документы и запросы)
2. Рассчитать релевантность ответов, при изменении документов (изменяются только документы)
3. Рассчитать релевантность ответов, при изменении запросов (изменяются только запросы)

Пример:
```cpp
SearchEngine searchEngine(ReadWriteJSONFile().readJSONFile(constants::configFilePath),
                              ReadWriteJSONFile().readJSONFile(constants::requestsFilePath));

//...
//Меняются документы и запросы
//...

//Рассчитать релевантность ответов (изменяются документы и запросы)
searchEngine.searchModifiedAll();

//...
//Меняются документы
//...

//Рассчитать релевантность ответов, при изменении документов (изменяются только документы)
searchEngine.searchModifiedDocuments();

//...
//Меняются запросы
//...

//Рассчитать релевантность ответов, при изменении запросов (изменяются только запросы)
searchEngine.searchModifiedRequests();
```

## Тестирование

В проекте использована система юнит-тестирования [GoogleTest](https://github.com/google/googletest); реализована как отдельный проект, - в репозитории в директории "tests" имеются исходные тесты. С помощью них тестируются основные классы, а именно: логика рассчёта релевантности (ядро программы), чтение файлов конфигурации и ответов и проверка их содержимого, создание JSON-объекта ответов. Подробно о функциях тестирования можно ознакомиться в [документации](./docs/ru/index.md). 

## Документация

Документацию пожно получить по [ссылке](./docs/ru/index.md), где приводится архитектура проекта и подробное описание классов.

## Лицензия

Этот класс лицензирован в соответствии с [MIT License](https://opensource.org/licenses/MIT).\
Copyright (c) 2025 Alexander Kazmirchuk

* * *

- Проект содержит копию библиотеки [nlohmann/json](https://github.com/nlohmann/json) Нильса Ломанна, лицензированную в соответствии с [MIT License](https://opensource.org/licenses/MIT).
- Также проект использует компоненты библиотеки [boost](https://www.boost.org), лицензированную в соответствии с [The Boost Software License](https://www.boost.org/users/license.html).

## Поддержка

Если у вас возникли сложности или вопросы по использованию программы или библиотеки, создайте 
[обсуждение](https://github.com/AVKazmirchuk/SearchEngine/issues/new) в данном репозитории или напишите на электронную почту <a_kazmirchuk@mail.ru>.



