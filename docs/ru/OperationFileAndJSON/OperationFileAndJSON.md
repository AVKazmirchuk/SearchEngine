
# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)
Библиотека использует основной класс kav::OperationFileAndJSON и вспомогательный класс kav::CheckJSON.\
Использует для своей работы следующие компоненты (объявлены в глобальной области видимости для возможного использования вне классов):
1. Перечисление кодов ошибок работы с файлами (enum class kav::ErrorCode).
2. Описание кодов ошибок (static const std::map<ErrorCode, std::string> kav::descriptionErrorCode).

В подробном описании эти компоненты не нуждаются, так как очевидно их использование.

## Класс kav::OperationFileAndJSON
Класс реализует чтение и запись файлов с проверкой, а также проверку JSON-объектов.
### Выполняет следующие функции:
1. Читает JSON-файл.
2. Записывает JSON-файл.
### Конструкторы:
```cpp
ReadWriteJSONFile() = default;
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Прочитать JSON-файл:
```cpp
static JSON readJSONFile(const std::string& filePath);
```
Параметры: путь JSON-файла\
Возвращаемое значение: JSON-файл
#### Записать JSON-файл:
```cpp
static void writeJSONFile(const JSON& objectJSON, const std::string& filePath);
```
Параметры: JSON-объект, путь JSON-файла
### Примеры
```cpp
#include "readWriteJSONFile.h"

int main()
{
    //...
    //Получить путь JSON-файла (filePath)
    //...

    //Прочитать JSON-файл
    JSON JSONObj{ReadWriteJSONFile::readJSONFile(filePath)};
    //Записать JSON-файл
    ReadWriteJSONFile::writeJSONFile(JSONObj, filePath);
}
```
