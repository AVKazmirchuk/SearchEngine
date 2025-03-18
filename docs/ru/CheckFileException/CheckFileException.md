# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс CheckFileException
Класс реализует генерацию исключений.
### Выполняет следующие функции:
1. Выбрасывает исключения.
2. Возвращает описание исключения.
3. Возвращает код ошибки исключения.
### Конструкторы:
```cpp
CheckFileException(ErrorCode in_errorCode, const std::string& in_information = "")
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

