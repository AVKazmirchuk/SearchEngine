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
В поле "requests" прописываются сами запросы; по ним будет вестись поиск в документах

### Скомпилированная программа

Для запуска программы надо просто запустить файл search_engine.exe без ключей.\
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
Документацию пожно получить по [ссылке](./docs/ru/index.md), где приводится архитектура проекта и подробное описание классов.

## Лицензия

Этот класс лицензирован в соответствии с [MIT License](https://opensource.org/licenses/MIT).
Copyright (c) 2025 Alexander Kazmirchuk

* * *

- Проект содержит копию [nlohmann/json](https://github.com/nlohmann/json) от Нильса Ломанна, лицензированную в соответствии с [MIT License](https://opensource.org/licenses/MIT).

## Поддержка

https://goformarty.github.io/How-to-README/
https://dan-it.gitlab.io/fe-book/teamwork/readme.html/
https://www.ionos.ca/digitalguide/websites/web-development/readme-file/
https://doka.guide/recipes/github-add-readme/

https://yandex.ru/search/?text=%D0%BA%D0%B0%D0%BA+%D0%BF%D1%80%D0%BE%D0%BF%D0%B8%D1%81%D0%B0%D1%82%D1%8C+cmake+%D0%B2+clion+%D0%B4%D0%BB%D1%8F+gtest+%D0%B4%D0%BB%D1%8F+%D0%BC%D0%BD%D0%BE%D0%B3%D0%BE%D1%83%D1%80%D0%BE%D0%B2%D0%BD%D0%B5%D0%BD%D0%BE%D0%B3%D0%BE+%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82%D0%B0&clid=2270455&banerid=0702004923%3A15287930302275780607%3A65fbc45a2cc6481e8c1741ae&win=638&lr=38

https://github.com/fortunevictim/how-to-install-googletests-on-CLion

https://stackoverflow.com/questions/33638433/setup-google-test-in-clion

https://yandex.ru/search/?text=%D0%BA%D0%B0%D0%BA+%D0%B2+CLion+%D1%81+%D0%BF%D0%BE%D0%BC%D0%BE%D1%89%D1%8C%D1%8E+CMake+%D0%BD%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B8%D1%82%D1%8C+%D0%BF%D1%80%D0%BE%D0%B5%D0%BA%D1%82+%D1%81+%D1%82%D0%B5%D1%81%D1%82%D0%B0%D0%BC%D0%B8+%D0%BD%D0%B0+%D0%BE%D1%81%D0%BD%D0%BE%D0%B2%D0%B5+Google+Test+%D0%B4%D0%BB%D1%8F+%D0%BC%D0%BD%D0%BE%D0%B3%D0%BE%D1%83%D1%80%D0%BE%D0%B2%D0%BD%D0%B5%D0%B2%D0%BE%D0%B9+%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D1%83%D1%80%D1%8B&lr=38&clid=2270455&win=638

https://raymii.org/s/tutorials/Cpp_project_setup_with_cmake_and_unit_tests.html

https://dev.to/basman/a-barebones-c-library-template-using-cmake-and-google-test-44hj

https://nuancesprog.ru/p/15603/

https://askdev.ru/q/nastroyka-testa-google-v-clion-94004/

https://www.jetbrains.com.cn/en-us/help/clion/quick-cmake-tutorial.html#cmake-debug

https://dzen.ru/a/Z4QqiDatYHRrWrzX

https://dev.to/yanujz/getting-started-with-googletest-and-cmake-1kgg

https://www.mo4tech.com/4-use-googletest.html

https://programmersought.com/article/896110219650/

https://www.kaizou.org/2014/11/gtest-cmake.html

https://www.tutorialspoint.com/gtest/gtest-first-test.htm




