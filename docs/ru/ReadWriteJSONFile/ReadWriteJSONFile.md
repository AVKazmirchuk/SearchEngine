
# SearchEngine
Документация SearchEngine на русском

### [Оглавление](../index.md)

## Класс ReadWriteJSONFile
Класс реализует чтение и запись JSON-файлов\
\
&emsp;&emsp;Выполняет следующие функции:
		
1. Читает JSON-файл
2. Записывает JSON-файл\
\
&emsp;Конструкторы:
```cpp
ReadWriteJSONFile() = default;
```
&emsp;Является: копируемым (неявно) и перемещаемым (неявно)\
\
&emsp;Общедоступные функции-члены:\
Прочитать JSON-файл
```cpp
JSON readJSONFile(const std::string& filePath);
```
Записать JSON-файл
```cpp
void writeJSONFile(const JSON& objectJSON, const std::string& filePath);
```
