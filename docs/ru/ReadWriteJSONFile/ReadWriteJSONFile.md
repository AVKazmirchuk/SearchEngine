
# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс ReadWriteJSONFile
Класс реализует чтение и запись JSON-файлов.
### Выполняет следующие функции:
1. Читает JSON-файл.
2. Записывает JSON-файл.
### Конструкторы:
```cpp
ReadWriteJSONFile() = default;
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
Прочитать JSON-файл:
```cpp
JSON readJSONFile(const std::string& filePath);
```
Записать JSON-файл:
```cpp
void writeJSONFile(const JSON& objectJSON, const std::string& filePath);
```
