# SearchEngine

Программа осушествляет поиск в документах по запросам и выдаёт релевантные ответы.

## Описание

В организациях бывает потребность поиска информации по базе документов. Программе указываются в файлах JSON пути документов и запросы. По документам строится база инвертированного индекса, на основе которого определяется релевантность ответа (содержимого документа) для каждого запроса. По завершении поиска результаты выводятся в файл JSON, где для каждого запроса указан документ со степенью релевантности.\
\
В проекте использована многопоточная обработка (стандартные библиотеки), - где необходимо. Использована сторонняя библиотека для работы с форматом JSON - [nlohmann/json](https://github.com/nlohmann/json). 
Проект может быть использован в виде готовой программы (консольного типа) или как библиотека. Архитектура и подробное описание классов приводится в [документации](./docs/ru/index.md).

## Зависимости

Программа была разработана и протестирована на С++ версии 17

## Установка

Все необходимые файлы (заголовочные и реализации) находятся в директориях "include" и "src". Также необходимо скопировать файлы config.json и requests.json (конфигурации программы и запросов) в корень проекта рядом с основным файлом CMakeLists.txt.\
Чтобы использовать проект как библиотеку небходимо подключить библиотеку [nlohmann/json](https://github.com/nlohmann/json/#integration) и отдельно скопировать файлы из папок "include" и "src" в свой проект в соотвествующие папки.\
Чтобы использовать проект как готовую программу, можно скачать релиз или скомпилировать из своего ранее созданного проекта.

## Как использовать проект

Программа использует файлы конфигурации и запросов (config.json и requests.json).\
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
В поле "files" прописываются пути до файлов документов. В поле "max_responses" указывается максимальное количество ответов (количество документов для каждого запроса). Назначение других полей очевидно.\ 
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
В поле "requests" прописываются сами запросы; по ним будет вестись поиск в документах

### Скомпилированная программа

Для запуска программы просто запустить файл search_engine.exe без ключей.\
Для работы необходимо чтобы файлы конфигурации и запросов (config.json и requests.json) находились в директории с программой. В этой же директории по окончании поиска будет создан файл ответов (answers.json).

### Как библиотека

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
Так же есть функция ...

## Тестирование


## Документация
Документацию пожно получить по [ссылке](./docs/ru/index.md)



## Поддержка

https://goformarty.github.io/How-to-README/
https://dan-it.gitlab.io/fe-book/teamwork/readme.html
https://www.ionos.ca/digitalguide/websites/web-development/readme-file/
https://doka.guide/recipes/github-add-readme/
