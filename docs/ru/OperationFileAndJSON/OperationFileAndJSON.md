
# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)
Библиотека использует основной класс kav::OperationFileAndJSON и вспомогательный класс kav::CheckJSON (описываться не будет из-за своей простоты, но объявлен в глобальной области видимости).\
Использует для своей работы следующие компоненты (объявлены в глобальной области видимости для возможного использования вне классов):
1. Перечисление кодов ошибок работы с файлами (enum class kav::ErrorCode).
2. Описание кодов ошибок (static const std::map<ErrorCode, std::string> kav::descriptionErrorCode).

В подробном описании эти компоненты не нуждаются, так как очевидно их использование.

## Класс kav::OperationFileAndJSON
Класс реализует чтение и запись файлов с проверкой, а также проверку JSON-объектов.
### Выполняет следующие функции:
1. Читает текстовый файл.
2. Читает/записывает JSON-файл.
5. Проверяет JSON-объект (при чтениии файла) на целостность структуры.
6. Проверяет JSON-объект на соотвествие структуры шаблону.
7. Проверяет файл на существование.
8. Проверяет файл на возможность открытия при чтении/записи.
9. Проверяет файл на возникновение ошибок чтения/записи.
10. Проверяет на пустоту массивы JSON-объектов.
### Конструкторы:
```cpp
OperationFileAndJSON() = delete;
```
Отсутствуют. Класс имеет только статические функции-члены.
### Общедоступные функции-члены:
#### Записать JSON-файл:
```cpp
static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const int formatByWidth = 2);
```
Параметры: ссылка на путь JSON-файла, ссылка на JSON-объект для записи, ширина отступа.\
Возвращаемое значение: код ошибки.
#### Проверить JSON-структуру на соответствие шаблону:
```cpp
static ErrorCode checkJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);
```
Параметры: ссылка на JSON-объект для проверки, ссылка на JSON-объект шаблона.\
Возвращаемое значение: код ошибки.
#### Проверить массив JSON-объекта на пустоту:
```cpp
static ErrorCode checkArray(const JSON &objectJSON);
```
Параметры: ссылка на JSON-объект для проверки.\
Возвращаемое значение: код ошибки.
#### Прочитать JSON-файл:
```cpp
static std::pair<JSON, ErrorCode> readJSONFile(const std::string &filePath);
```
Параметры: ссылка на путь JSON-файла.\
Возвращаемое значение: пара JSON-объекта и кода ошибки.
#### Прочитать текстовый файл:
```cpp
static std::pair<std::string, ErrorCode> readTextFile(const std::string &filePath);
```
Параметры: ссылка на путь текстового файла.\
Возвращаемое значение: пара текста и кода ошибки.
### Примеры
```cpp
#include "kav/operationFileAndJSON.h"

int main()
{
   //...
   //Получить ссылку на JSON-объект для проверки (objectJSON)
   //...

   //Проверить массив JSON-объекта на пустоту
   kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkArray(objectJSON)};
      
  //...
  //Получить ссылку на путь текстового файла (filePath)
  //...

  //Прочитать текстовый файл
    std::pair<std::string, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readTextFile(filePath)};

  //...
  //Получить ссылку на путь JSON-файла (filePath)
  //...

  //Прочитать JSON-файл
  std::pair<JSON, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readJSONFile(filePath)};

  //...
  //Получить ссылку на JSON-объект для проверки (objectJSON), ссылку на JSON-объект шаблона (objectJSONTemplate)
  //...

  //Проверить JSON-структуру на соответствие шаблону
  kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkJSONStructureMatch(objectJSON, objectJSONTemplate)};

  //...
  //Получить ссылку на путь JSON-файла (filePath), ссылку на JSON-объект для записи (objectJSON), ширину отступа (formatByWidth)
  //...

  //Записать JSON-файл
  kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::writeJSONFile(filePath, objectJSON, formatByWidth)};
}
```
