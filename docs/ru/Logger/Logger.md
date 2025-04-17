# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс Logger
Класс реализует логирование событий. Для настройки класса используется файл конфигураци.
### Выполняет следующие функции:
1. Выводит события разного уровня в консоль.
### Файл конфигурации
Класс использует файл конфигурации (logger.json) для настройки логирования.\
\
Файл logger.json:
```json
{
	"usageTimeLimit" : {
		"seconds" : 0,
		"minutes" : 0,
		"hours" : 0,
		"days" : 1,
		"weeks" : 0
	},
	"storageTimeLimit" : {
		"seconds" : 0,
		"minutes" : 0,
		"hours" : 0,
		"days" : 0,
		"weeks" : 1
	},
	"dateTimeFormat" : "%Y-%m-%d %H:%M:%S",
	"fileNameFormat" : "%Y-%m-%d_%H-%M-%S",
	"fileSizeLimit" : 1048576,
	"filesDirectory" : ".\\Logs\\"
}

```
Назначение полей:
- storageTimeLimit: интервалы времени хранения файла
  - weeks: недели
  - days: дни
  - hours: часы
  - minutes: минуты
  - seconds: секунды
  
- usageTimeLimit: интервалы времени использования файла
  - weeks: недели
  - days: дни
  - hours: часы
  - minutes: минуты
  - seconds: секунды
  
- dateTimeFormat: формат даты и времени записи в файл
- fileNameFormat: формат имени файла
- fileSizeLimit: предельный размер файла
- filesDirectory: директория с файлами
### Конструкторы:
```cpp
Logger() = default;
```
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Инициализировать (настроить) класс
```cpp
static void initialize(const std::string& configFilePath);
```
Параметры: путь к файлу конфигурации
#### Записать сообщение уровня debug:
```cpp
static void debug(const std::string& message);
```
Параметры: ссылка на сообщение
#### Записать сообщение уровня debug:
```cpp
static void debug(const std::string& message, const std::exception& exception);
```
Параметры: ссылка на сообщение, ссылка на исключение
#### Записать сообщение уровня information:
```cpp
static void info(const std::string& message);
```
Параметры: ссылка на сообщение
#### Записать сообщение уровня information:
```cpp
static void info(const std::string& message, const std::exception& exception);
```
Параметры: ссылка на сообщение, ссылка на исключение
#### Записать сообщение уровня warning:
```cpp
static void warning(const std::string& message);
```
Параметры: ссылка на сообщение
#### Записать сообщение уровня warning:
```cpp
static void warning(const std::string& message, const std::exception& exception);
```
Параметры: ссылка на сообщение, ссылка на исключение
#### Записать сообщение уровня error:
```cpp
static void error(const std::string& message);
```
Параметры: ссылка на сообщение
#### Записать сообщение уровня error:
```cpp
static void error(const std::string& message, const std::exception& exception);
```
Параметры: ссылка на сообщение, ссылка на исключение
#### Записать сообщение уровня fatal:
```cpp
static void fatal(const std::string& message);
```
Параметры: ссылка на сообщение
#### Записать сообщение уровня fatal:
```cpp
static void fatal(const std::string& message, const std::exception& exception);
```
Параметры: ссылка на сообщение, ссылка на исключение
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
    Logger::initialize(configFilePath);

    //...
    //Получить сообщение уровня debug (message)
    //...

    //Записать сообщение уровня debug
    Logger::debug(message);

    //...
    //Получить сообщение уровня information (message)
    //...

    //Записать сообщение уровня information
    Logger::info(message);

    //...
    //Получить сообщение уровня warning (message)
    //...

    //Записать сообщение уровня warning
    Logger::warning(message);

    //...
    //Получить сообщение уровня error (message)
    //...

    //Записать сообщение уровня error
    Logger::error(message);

    //...
    //Получить сообщение уровня fatal (message)
    //...

    //Записать сообщение уровня fatal
    Logger::fatal(message);
}
```

