# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс ReadTextFile
Класс реализует чтение текстовых файлов\
\
&emsp;&emsp;Выполняет следующие функции:
		
1. Читает текстовый файл\
\
&emsp;Конструкторы:
```cpp
ReadTextFile() = default;
```
&emsp;Является: копируемым (неявно) и перемещаемым (неявно)\
\
&emsp;Общедоступные функции-члены:\
Прочитать документы в отдельных потоках
```cpp
std::vector<std::string> readTextFile(const std::vector<std::string>& filePaths);
```
