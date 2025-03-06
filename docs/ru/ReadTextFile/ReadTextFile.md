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
### Общедоступные функции-члены:\
Прочитать документы в отдельных потоках:
```cpp
std::vector<std::string> readTextFile(const std::vector<std::string>& filePaths);
```
