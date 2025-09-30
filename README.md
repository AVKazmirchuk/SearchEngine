# SearchEngine

Программа осушествляет поиск в документах по запросам и выдаёт релевантные ответы.

## Описание

В организациях бывает потребность поиска информации по базе документов. Программе указываются в файлах JSON пути документов и запросы. По документам строится база инвертированного индекса, на основе которого определяется релевантность ответа (содержимого документа) для каждого запроса. По завершении поиска результаты выводятся в файл JSON, где для каждого запроса указан документ со степенью релевантности.\
\
В проекте использована многопоточная обработка (использована стандартная библиотека), - где необходимо.\
Проект состоит из основной части (ядро), двух библиотек (kav_check, kav_logger) и монитора (kav_logger_monitor). Все части подробно описаны в документации.\
Проект может быть использован в виде готовой программы консольного типа, скачанной из репозитария, или собран и скомпилирован самостоятельно.\
Архитектура и подробное описание всех классов приводится в [документации](./docs/ru/index.md).

## Зависимости

Программа была разработана на С++ версии 20 и протестирована на ОС MS Windows 10, MS Windows 11.\
Использованы следующие сторонние библиотеки:
- для работы с форматом JSON - [nlohmann/json](https://github.com/nlohmann/json/blob/develop/README.md);
- для межпроцессного обмена данными с помощью очереди сообщений - [boost/interprocess/ipc/message_queue](https://www.boost.org/doc/libs/master/doc/html/interprocess/synchronization_mechanisms.html#interprocess.synchronization_mechanisms.message_queue);
- для предоставления местоположения в исходном коде - [boost/assert/source_location](https://www.boost.org/doc/libs/latest/libs/assert/doc/html/assert.html#:~:text=for%20security%20reasons.-,Source%20Location%20Support%2C%20%3Cboost/assert/source_location.hpp%3E,-Description);
- для вывода информации на консоль в цвете - [Termcolor](https://github.com/ikalnytskyi/termcolor/blob/master/README.rst);
- для юнит-тестирования - [GoogleTest](https://github.com/google/googletest/blob/main/googletest/README.md).

Для интеграции библиотек в проект можно воспользоваться следующими ссылками:
- библиотека [nlohmann/json](https://github.com/nlohmann/json/#integration);
- библиотека [boost](https://www.boost.org/doc/libs/1_88_0/more/getting_started/windows.html);
- библиотека [Termcolor](https://github.com/ikalnytskyi/termcolor/blob/master/README.rst#installation);
- библиотека [GoogleTest](https://github.com/google/googletest/blob/main/googletest/README.md).

Для запуска программы, скаченной из репозитория, не требуется устанавливать дополнительные компоненты. Программа скомпилирована с необходимыми статическими библиотеками. 

## Установка

Для использования проекта можно склонировать репозиторий или вручную добавить библиотеки. Все необходимые файлы CMakeLists.txt в подпроектах сконфигурированы и все библиотеки добавлены, кроме boost.\
В проекте использованы четыре подпроекта: 
- основной проект (search_engine-solution), - основная программа поиска слов в документах и рассчёта релевантности ответов;
- три независимых подпроекта:
  - kav_check - библиотека для работы с файлами;
  - kav_logger - библиотека для логирования событий в файл и вывода на консоль;
  - kav_logger_monitor - консоль вывода сообщений работы основной программы.

Все необходимые файлы (документация, заголовочные, реализации, конфигурации, запросов, ответов, тестовых) находятся в директориях:
- docs - документация к проекту;
- include - общие заголовочные файлы;
- kav_logger_monitor - файлы подпроекта вывода сообщений на консоль;
- nlohmann_json - библиотека для работы с JSON-форматом;
- kav_check - библиотека для работы с файлами;
- kav_logger - библиотека для логирования событий в файл и вывода на консоль;
- resources - дополнительная директория файлов ресурсов для работы программы (как репозиторий);
- src - исходные файлы;
- tests - файлы для тестирования;
- runtime - содержит все необходимые конфигурационные файлы, включая два файла основной программы и монитора. Сделано для удобства. Для изменения можно поправить файл CMakeLists.txt в корне проекта и подпроекта монитор
(можно определить по комментариям). 


Для работы с исходными файлами проекта небходимо (в общем случае):
1. Скопировать файлы config.json, logger.json, requests.json, messageQueue.json (конфигурации и запросов) из репозитория директории "resources" в директорию с исполняемым файлом основоного проекта search-engine.exe.
2. Скопировать файл logger_monitor.exe из директории подпроекта "kav_logger_monitor" в директорию с исполняемым файлом основного проекта search-engine.exe.
3. Скопировать директорию "resources" из репозитория директории "resources" в директорию с исполняемым файлом основного проекта search-engine.exe. В этой директории находятся три документа для примера, по которым осуществляется поиск.
4. Подключить библиотеку [nlohmann/json](https://github.com/nlohmann/json/#integration) (в проекте это уже сделано).
5. Подключить библиотеку [boost/interprocess/ipc/message_queue](https://www.boost.org/doc/libs/1_88_0/more/getting_started/windows.html) самостоятельно.
6. Подключить библиотеку юнит-тестирования [GoogleTest](https://github.com/google/googletest/blob/main/googletest/README.md) (в проекте это уже сделано).
7. Подключить библиотеку [Termcolor](https://github.com/ikalnytskyi/termcolor/blob/master/README.rst#installation) (в проекте это уже сделано).
8. Подключить библиотеку kav_check (в проекте это уже сделано).
9. Подключить библиотеку kav_logger (в проекте это уже сделано).


Чтобы использовать готовую программу:
- можно скачать релиз (уже содержит все необходимые файлы);
- или скомпилировать из своего проекта собранного вручную. Все CMakeLists.txt в подпроектах и библиотеках достаточно прокомментированы и не должны вызвать сложность.

То есть, в любом случае вы получаете начальную готовую структуру для немедленного применения.

## Как использовать проект

Программа использует файлы конфигурации и запросов (config.json, logger.json, messageQueue.json и requests.json). По результатам поиска в документах по запросам формируется файл answers.json, находящийся по этому же пути, что и запускной файл.\
Файл config.json:
```json
{
  "config": {
    "name": "SearchEngine",
    "version": "1.0.0",
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
В поле "requests" прописываются сами запросы; по ним будет вестись поиск в документах.
\
Файл logger.json:
```json
{
	"usageTimeLimit" : {
		"seconds" : 0,
		"minutes" : 1,
		"hours" : 0,
		"days" : 0,
		"weeks" : 0
	},
	"storageTimeLimit" : {
		"seconds" : 0,
		"minutes" : 7,
		"hours" : 0,
		"days" : 0,
		"weeks" : 0
	},
	"dateTimeFormat" : "%Y-%m-%d %H:%M:%S",
	"fileNameFormat" : "%Y-%m-%d_%H-%M-%S",
	"fileSizeLimit" : 2000,
	"filesDirectory" : ".\\Logs\\"
}
```
В полях "usageTimeLimit", "storageTimeLimit" указываются значения использования (записи) и хранения файла логирования соответственно. Назначение других полей очевидно.
\
Файл messageQueue.json:
```json
{
    "messageQueue" : {
        "nameOfQueue" : "search_engine",
        "maxNumberOfMessages" : 100,
        "maxMessageSize" : 1024,
        "fileNameOfMainProgram" : "search_engine.exe",
        "fileNameOfMonitor" : "logger_monitor.exe",
        "nameOfConsole" : "Logger Monitor",
        "indicatesMonitorStarting" : "C:\\Windows\\Temp\\logger_monitor"
    }
}
```
В полях указаны значения для создания очереди сообщений и синронизации работы между двумя процессами search_engine.exe и logger_monitor.exe. Поле "indicatesMonitorStarting" является сигналом готовности процесса logger_monitor.exe.
\
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

### Запуск программы

Для запуска программы надо просто запустить файл search_engine.exe без ключей.\
Для работы необходимо, чтобы файлы конфигурации и запросов (config.json, logger.json, messageQueue.json и requests.json) находились в директории с программой. В этой же директории по окончании поиска будет создан файл ответов answers.json.

### Рассчёт релевантности

Для использования в самой программе (в функции main) необходимо оперировать объектом класса SearchEngine. Он уже в свою очередь управляет взаимодействием между другими классами.\
Есть следующие функции рассчёта релевантности:
1. Рассчитать релевантность ответов (изменяются документы и запросы)
2. Рассчитать релевантность ответов, при изменении документов (изменяются только документы)
3. Рассчитать релевантность ответов, при изменении запросов (изменяются только запросы)

Пример:
```cpp
//Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
SearchEngine searchEngine(constants::configFilePath, constants::requestsFilePath, constants::answersFilePath, constants::precision, constants::formatByWidth);

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

В проекте использована система юнит-тестирования [GoogleTest](https://github.com/google/googletest), - в репозитории в директории "tests" имеются исходные тесты. С помощью них тестируется логика рассчёта релевантности (ядро программы) и создание JSON-объекта ответов. Также есть тесты для бибилиотеки kav_check. Для библиотеки kav_logger и подпроекта "kav_logger_monitor" тесты отсутствуют. Подробно о функциях тестирования можно ознакомиться в [документации](./docs/ru/index.md). 

## Документация

Документацию пожно получить по [ссылке](./docs/ru/index.md), где приводится архитектура проекта и подробное описание классов.

## Лицензия

Этот проект лицензирован в соответствии с [MIT License](https://opensource.org/licenses/MIT).\
Copyright (c) 2025 Alexander Kazmirchuk

* * *

- Проект содержит копию библиотеки [nlohmann/json](https://github.com/nlohmann/json) Нильса Ломанна, лицензированную в соответствии с [MIT License](https://opensource.org/licenses/MIT).
- Также проект использует компоненты библиотеки [boost](https://www.boost.org), лицензированную в соответствии с [The Boost Software License](https://www.boost.org/users/license.html).
- Также проект использует библиотеку юнит-тестирования [GoogleTest](https://github.com/google/googletest/blob/main/README.md), лицензированную как [BSD 3-Clause "New" or "Revised" License](https://github.com/google/googletest/blob/main/LICENSE).
- Также проект использует библиотеку [Termcolor](https://github.com/ikalnytskyi/termcolor/blob/master/README.rst) Ihor Kalnytskyi, лицензированную как BSD (3-clause) License.

## Поддержка

Если у вас возникли сложности или вопросы по использованию программы или библиотеки, создайте 
[обсуждение](https://github.com/AVKazmirchuk/SearchEngine/issues/new) в данном репозитории или напишите на электронную почту <a_kazmirchuk@mail.ru>.



