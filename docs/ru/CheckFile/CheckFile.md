# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс CheckFile
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
#### Проверить файл на целостность JSON-структуры:
```cpp
static bool isJSONStructureValid(const std::string &fileName);
```
Параметры: ссылка на имя файла
Возвращаемое значение: целостность JSON-структуры 
#### Проверить JSON-структуру файла на соответствие шаблону:
```cpp
static bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);
```
Параметры: ссылка на проверяемый JSON-объект, ссылка на JSON-объект шаблона
Возвращаемое значение: соотвествие JSON-структуры шаблону
### Примеры
```cpp
#include "checkFile.h"

int main()
{
    //...
    //Получить имя файла (fileName)
    //...
    
    //Проверить файл на целостность JSON-структуры
    bool JSONStructureValid{CheckFile::isJSONStructureValid(fileName)};

    //...
    //Получить JSON-объекты шаблона и проверяемого (objectJSONTemplate, objectJSON)
    //...

    //Проверить JSON-структуру файла на соответствие шаблону
    bool JSONStructureMatch{CheckFile::isJSONStructureMatch(objectJSONTemplate, objectJSON)};
}
```
