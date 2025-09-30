# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс ReadTextFile
Класс реализует чтение текстовых файлов.
### Выполняет следующие функции:
1. Читает текстовый файл.
### Конструкторы:
```cpp
ReadTextFile() = default;
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Прочитать документы в отдельных потоках:
```cpp
static std::vector<std::string> readTextFile(const std::vector<std::string>& filePaths);
```
Параметры: список путей документов\
Возвращаемое значение: база документов
### Примеры
```cpp
#include "readTextFile.h"

int main()
{
    //...
    //Получить cписок путей документов (filePaths)
    //...

    //Прочитать документы в отдельных потоках
    std::vector<std::string> documents{ReadTextFile::readTextFile(filePaths)};
}
```
