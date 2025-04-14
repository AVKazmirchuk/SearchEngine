# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс Logger
Класс реализует логирование событий.
### Выполняет следующие функции:
1. Выводит события разного уровня в консоль.
### Конструкторы:
```cpp
Logger() = default;
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Инициализировать (настроить) класс
```cpp
void initialize(const std::string& configFilePath);
```
#### Записать сообщение уровня information:
```cpp
void info(const std::string& message);
```
Параметры: Сообщение
#### Записать сообщение уровня warning:
```cpp
void warning(const std::string& message);
```
Параметры: Сообщение
#### Записать сообщение уровня error:
```cpp
void error(const std::string& message);
```
Параметры: Сообщение
#### Записать сообщение уровня fatal:
```cpp
void fatal(const std::string& message);
```
Параметры: Сообщение
### Примеры
```cpp
#include "logger.h"

int main()
{
    //Создать объект класса Logger
    Logger loggerObj;

    //...
    //Получить путь файла настроек (configFilePath)
    //...

    //Инициализировать (настроить) класс
    void initialize(const std::string& configFilePath);

    //...
    //Получить сообщение уровня information (message)
    //...

    //Записать сообщение уровня information
    loggerObj.info(message);

    //...
    //Получить сообщение уровня warning (message)
    //...

    //Записать сообщение уровня warning
    loggerObj.warn(message);

    //...
    //Получить сообщение уровня error (message)
    //...

    //Записать сообщение уровня error
    loggerObj.error(message);

    //...
    //Получить сообщение уровня fatal (message)
    //...

    //Записать сообщение уровня fatal
    loggerObj.fatal(message);
}
```

