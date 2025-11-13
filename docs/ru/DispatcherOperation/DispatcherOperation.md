# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс DispatcherOperations
Класс реализует диспетчер операций c файлами и JSON-объектами.\
Логирование операций при наличии ошибок происходит именно в этом классе. В вызывающей функции логировать не надо.\
Если требуется логирование в любом случае (без ошибки) - тогда надо логировать при вызове операции (пока сделано так, но надо предусмотреть и эту возможность).
### Выполняет следующие функции:
1. Читает текстовый файл.
2. Читает/записывает JSON-файл.
5. Проверяет JSON-объект (при чтениии файла) на целостность структуры.
6. Проверяет JSON-объект на соотвествие структуры шаблону.
7. Проверяет файл на существование.
8. Проверяет файл на возможность открытия при чтении/записи.
9. Проверяет файл на возникновение ошибок чтения/записи.
10. Проверяет на пустоту массивы путей файлов и запросов JSON-объектов.
11. В соответствии с уровнем логирования при наличии ошибки выбрасывает исключение и/или логирует в журнал.

Класс использует для своей работы следующие компоненты (объявлены в глобальной области видимости для возможного использования вне класса):
1. Перечисление уровней логирования (enum class ErrorLevel).
2. Перечисление кодов ошибок работы с файлами (enum class ErrorCode).
3. Описание кодов ошибок (static const std::map<ErrorCode, std::string> descriptionErrorCode).
4. Структура результатов чтения текстовых файлов (одновременное чтение в нескольких потоках) (struct ResultOfReadMultipleTextFiles).

Также класс использует класс исключения OperationException (закрытый класс) для выброса исключений при ошибке уровня логирования ErrorLevel::fatal.\
В подробном описании эти компоненты не нуждаются, так как очевидно их использование.

### Конструкторы:
```cpp
DispatcherOperations() = delete;
```
Отсутствуют. Класс имеет только статические функции-члены. 

### Наиболее важные (интересные) закрытые функции-члены индексации документов:
#### Алгоритм подсчёта инвертированного индекса и наполнения базы:
- вызов функции "readMultipleTextFilesImpl". Разбивает файлы для чтения на группы. В каждой группе количество файлов равно количеству всех файлов делённое на количество потоков (рассчитанное заранее). 
  И запускает в отдельных потоках функцию "readTextFile" и сохраняет документ в общем контейнере под своим ID.
  - вызов функции "readTextFile". Читает каждый файл.

Таким образом, после завершения работы всех потоков получается контейнер, содержащий документы в соответствии с ID. Причём, для записи документов в общий контейнер мьютексы не нужны, так как, каждый документ сохраняется 
со своим ииндексом.
На выходе функции "readMultipleTextFilesImpl" формируется база документов.
##### Производительность:
Замеры времени чтения файлов (обрабатывалось 843 документа, по 100'000 слов в каждом; 16-ти ядерный процессор):
| Количество потоков | Время, сек |
|--------------------|------------|
| 1 поток            |   1,284    |
| 15 потоков         |   0,318    |

Как видно, при этом алгоритме разница по времени в 4 раза.\
Стоит отметить, что всё вышесказанное справедливо только для указанного количества файлов и размера каждого файла. При других значениях разница в производительности будет другой.
### Общедоступные функции-члены:
#### Записать JSON-файл:
```cpp
static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const int formatByWidth = 2,
                                   ErrorLevel errorLevel = ErrorLevel::no_level, const std::string &message = "",
                                   const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на путь JSON-файла, ссылка на JSON-объект для записи, ширина отступа, уровень логирования, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: код ошибки.
#### Проверить JSON-структуру на соответствие шаблону:
```cpp
static ErrorCode checkJSONStructureMatch(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                            ErrorLevel errorLevel = ErrorLevel::no_level, const std::string &message = "",
                            const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на путь JSON-файла, ссылка на JSON-объект для проверки, ссылка на JSON-объект шаблона, уровень логирования, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: код ошибки.
#### Проверить массив JSON-объекта путей файлов на пустоту:
```cpp
static ErrorCode checkFilePathsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::no_level,
                                         const std::string &message = "",
                                         const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на JSON-объект для проверки, уровень логирования, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: код ошибки.
#### Проверить массив JSON-объекта запросов на пустоту:
```cpp
static ErrorCode checkRequestsArray(const JSON &objectJSON, ErrorLevel errorLevel = ErrorLevel::no_level,
                                        const std::string &message = "",
                                        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на JSON-объект для проверки, уровень логирования, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: код ошибки.
#### Прочитать JSON-файл:
```cpp
static std::pair<JSON, ErrorCode> readJSONFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::no_level,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на путь JSON-файла, уровень логирования, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: пара JSON-объекта и кода ошибки.
#### Прочитать текстовый файл:
```cpp
static std::pair<std::string, ErrorCode>
    readTextFile(const std::string &filePath, ErrorLevel errorLevel = ErrorLevel::no_level,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на путь текстового файла, уровень логирования, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: пара текста и кода ошибки.
#### Прочитать несколько текстовых файлов одновременно в разных потоках:
```cpp
static ResultOfReadMultipleTextFiles readMultipleTextFiles(const std::vector<std::string>& filePaths,
                 const unsigned int desiredNumberOfThreads = std::thread::hardware_concurrency(),
                 const unsigned int maximumAllowableErrorsNumber = 1,
                 ErrorLevel errorLevelOneFile = ErrorLevel::no_level, ErrorLevel errorLevelMultipleFiles = ErrorLevel::no_level,
                 const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на путь контейнера путей файлов, желаемое количество потоков, максимально возможное количество ошибок, 
уровень логирования для одного фойла, уровень логирования для всех файлов, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: структура результатов чтения текстовых файлов.\
Реализация чтения документов в разных потоках проста и не требует пояснений (вполне достаточно комментариев).
### Примеры
```cpp
#include "readTextFile.h"

int main()
{
    //...
    //Получить ссылку на JSON-объект для проверки (objectJSON)
    //...

    //Проверить массив JSON-объекта путей файлов на пустоту
    DispatcherOperations::checkFilePathsArray(objectJSON);

   //...
   //Получить ссылку на JSON-объект для проверки (objectJSON)
   //...

   //Проверить массив JSON-объекта запросов на пустоту
   DispatcherOperations::checkRequestsArray(objectJSON);

   //...
   //Получить ссылку на путь контейнера путей файлов (filePaths)
   //...

  //Прочитать документы
  std::vector<std::string> documents{DispatcherOperations::readMultipleTextFiles(filePaths).first};

  //...
  //Получить ссылку на путь текстового файла (filePath)
  //...

  //Прочитать документ
  std::string document{DispatcherOperations::readTextFile(filePath).first};

  //...
  //Получить ссылку на путь JSON-файла (filePath)
  //...

  //Прочитать JSON-файл
  JSON configJSON{DispatcherOperations::readJSONFile(filePath).first};

  //...
  //Получить ссылку на путь JSON-файла (filePath), ссылку на JSON-объект для проверки (objectJSON), ссылку на JSON-объект шаблона (objectJSONTemplate)
  //...

  //Проверить JSON-структуру на соответствие шаблону
  DispatcherOperations::checkJSONStructureMatch(filePath, objectJSON, objectJSONTemplate);

  //...
  //Получить ссылку на путь JSON-файла (filePath), ссылку на JSON-объект для записи (objectJSON)
  //...

  //Записать JSON-файл
  DispatcherOperations::writeJSONFile(filePath, objectJSON);
}
```
