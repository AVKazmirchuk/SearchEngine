# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс DispatcherOperationValidity
Класс реализует диспетчер операций c файлами и JSON-объектами.\
Логирование операций при наличии ошибок происходит именно в этом классе. В вызывающей функции логировать не надо.\
Если требуется логирование в любом случае (без ошибки) - тогда надо логировать при вызове операции (пока сделано так, но надо предусмотреть и эту возможность).
### Выполняет следующие функции:
1. Читает/записывает текстовый файл.
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
\
В подробном описании эти компоненты не нуждаются, так как очевидно их использование.

### Конструкторы:
```cpp
DispatcherOperationValidity() = delete;
```
Отсутствуют. Класс имеет только статические функции-члены. 
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
static std::pair<std::vector<std::string>, ErrorCode> readMultipleTextFiles(const std::vector<std::string>& filePaths,
                 ErrorLevel errorLevel = ErrorLevel::no_level, const std::string &message = "",
                 const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);
```
Параметры: ссылка на путь контейнера путей файлов, уровень логирования, ссылка на сообщение, ссылка на вызывающую функцию.\
Возвращаемое значение: пара контейнер текстов и кода ошибки.
### Примеры
```cpp
#include "readTextFile.h"

int main()
{
    //...
    //Получить ссылку на JSON-объект для проверки (objectJSON)
    //...

    //Проверить массив JSON-объекта путей файлов на пустоту
    DispatcherOperationValidity::checkFilePathsArray(objectJSON);

   //...
   //Получить ссылку на JSON-объект для проверки (objectJSON)
   //...

   //Проверить массив JSON-объекта запросов на пустоту
   DispatcherOperationValidity::checkRequestsArray(objectJSON);

   //...
   //Получить ссылку на путь контейнера путей файлов (filePaths)
   //...

  //Прочитать документы
  std::vector<std::string> documents{DispatcherOperationValidity::readMultipleTextFiles(filePaths).first};

  //...
  //Получить ссылку на путь текстового файла (filePath)
  //...

  //Прочитать документ
  std::string document{DispatcherOperationValidity::readTextFile(filePath).first};

  //...
  //Получить ссылку на путь JSON-файла (filePath)
  //...

  //Прочитать JSON-файл
  JSON configJSON{DispatcherOperationValidity::readJSONFile(filePath).first};

  //...
  //Получить ссылку на путь JSON-файла (filePath), ссылку на JSON-объект для проверки (objectJSON), ссылку на JSON-объект шаблона (objectJSONTemplate)
  //...

  //Проверить JSON-структуру на соответствие шаблону
  DispatcherOperationValidity::checkJSONStructureMatch(filePath, objectJSON, objectJSONTemplate);

  //...
  //Получить ссылку на путь JSON-файла (filePath), ссылку на JSON-объект для записи (objectJSON)
  //...

  //Записать JSON-файл
  DispatcherOperationValidity::writeJSONFile(filePath, objectJSON);
}
```
