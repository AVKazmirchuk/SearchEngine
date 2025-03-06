# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс CheckFile
Класс реализует проверку файла и его содержимого\
\
&emsp;&emsp;Выполняет следующие функции:
		
1. Проверяет файл на существование.
2. Проверяет файл на пустоту.
3. Проверяет файл на целостность JSON-структуры.
4. Проверяет JSON-структуру файла на соответствие шаблону.\
\
&emsp;Конструкторы:\
```cpp
CheckFile() = default;
```
\
&emsp;Является: копируемым (неявно) и перемещаемым (неявно)\
\
&emsp;Общедоступные функции-члены:\
Проверить файл на существование
```cpp
bool isExist(const std::string &fileName);
```
Проверить файл на пустоту
```cpp
bool isEmpty(const std::string &fileName);
```
Проверить файл на целостность JSON-структуры
```cpp
 bool isJSONStructureValid(const std::string &fileName);
```
Проверить JSON-структуру файла на соответствие шаблону
```cpp
bool isJSONStructureMatch(const JSON &objectJSONTemplate, const JSON &objectJSON);
```
