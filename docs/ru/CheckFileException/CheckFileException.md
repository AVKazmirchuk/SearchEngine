# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс CheckFileException
Класс реализует проверку файла и его содержимого.
### Выполняет следующие функции:
1. Проверяет файл на существование.
2. Проверяет файл на пустоту.
3. Проверяет файл на целостность JSON-структуры.
4. Проверяет JSON-структуру файла на соответствие шаблону.
### Конструкторы:
```cpp
CheckFile() = default;
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Проверить файл на существование:
```cpp
bool isExist(const std::string &fileName);
```
Параметры: имя файла
Возвращаемое значение: существование файла
#### Проверить файл на пустоту:
```cpp
bool isEmpty(const std::string &fileName);
```
Параметры: имя файла
Возвращаемое значение: пустота файла
#### Проверить файл на целостность JSON-структуры:
```cpp
 bool isJSONStructureValid(const std::string &fileName);
```
Параметры: имя файла
Возвращаемое значение: целостность JSON-структуры 
#### Проверить JSON-структуру файла на соответствие шаблону:
```cpp
bool isJSONStructureMatch(const JSON &objectJSONTemplate, const JSON &objectJSON);
```
Параметры: JSON-объект шаблона, проверяемый JSON-объект
Возвращаемое значение: соотвествие JSON-структуры шаблону
### Примеры
```cpp
#include "checkFile.h"

int main()
{
    //Создать объект класса CheckFile
    CheckFile checkFileObj;

    //...
    //Получить имя файла (fileName)
    //...

    //Проверить файл на существование
    bool exist{checkFileObj.isExist(fileName)};
    //Проверить файл на пустоту
    bool empty{checkFileObj.isEmpty(const std::string &fileName)};
    //Проверить файл на целостность JSON-структуры
    bool JSONStructureValid{checkFileObj.isJSONStructureValid(fileName)};

    //...
    //Получить JSON-объекты шаблона и проверяемого (objectJSONTemplate, objectJSON)
    //...

    //Проверить JSON-структуру файла на соответствие шаблону
    bool JSONStructureMatch{checkFileObj.isJSONStructureMatch(objectJSONTemplate, objectJSON)};
}
```

