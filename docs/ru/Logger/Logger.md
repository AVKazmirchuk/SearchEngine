# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

Используется основной класс kav::Logger, класс исключения kav::LoggerException и вспомогательные закрытые классы kav::Logger::ConfigLogger, kav::Logger::WriterMessage, kav::Logger::WriterMessage::ConfigWriterMessage,  kav::Logger::ExceptionStub,  kav::Logger::OnlyOneObject. Вспомогательные классы подробно описываться не будут. В исходных файлах есть все необходимые комментарии, а так же приведена элементарная логика работы на схеме.

## Класс Logger
Класс реализует логирование событий в лог-файлы и в консоль (запускается как независимое приложение) посредством очереди сообщений.\
Для настройки класса используются файлы конфигураци: logger.json, messageQueue.json.\

### Выполняет следующие функции:
1. Записывает сообщения в лог-файлы.
2. Выводит события в консоль.

Эти функции осуществляются в другом потоке и приложении, чтобы минимизировать время ожидания обработки событий для основного потока. 
### Файлы конфигурации
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
	"fileSizeLimit" : 2000,
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

\
Класс использует файл конфигурации (messageQueue.json) для настройки очереди сообщений.\
\
Файл messageQueue.json:
```json
{
    "messageQueue" : {
        "nameOfQueue" : "search_engine",
        "maxNumberOfMessages" : 100,
        "maxMessageSize" : 1024,
        "fileNameOfMainProgram" : "search_engine.exe",
        "fileNameOfMonitor" : "logger_monitor.exe",
        "nameOfConsole" : "Logger Monitor",
        "indicatesMonitorStarting" : "C:\\Windows\\Temp\\logger_monitor"
    }
}
```
Назначение полей:
- nameOfQueue: имя очереди
- maxNumberOfMessages: максимальное количество сообщений в очереди
- maxMessageSize: максимальный размер сообщения
- fileNameOfMainProgram: имя файла основной программы
- fileNameOfMonitor: имя файла монитора
- nameOfConsole: имя консоли
- indicatesMonitorStarting: признак запуска монитора

### Конструкторы:
Создаёт объекты: СonfigLogger, WriterMessage. Настраивает класс Logger и запускает в отдельном потоке запись сообщений 
в лог-файл и отправку сообщений в монитор.
```cpp
Logger(const std::string &in_configLoggerFilePath, const std::string &in_configWriterMessageFilePath)
                : configLogger(in_configLoggerFilePath), writerMessage(in_configWriterMessageFilePath)
        {
            //Объект класса не создан
            if (ptrToLogger == nullptr)
            {
                //Получить адрес объекта
                ptrToLogger = this;

                //Настроить класс
                setup();

                //Запустить в отдельном потоке запись сообщения в лог-файл и отправку сообщения в монитор
                resultOfWriteToFileAndMonitor = std::async(&Logger::WriterMessage::run, &writerMessage);
            }
            else
            {
                //Выбросить исключение, так как более обного объекта создавать запрещено
                throw OnlyOneObject();
            }
        }
```
Параметры: путь файла конфигурации логирования, путь файла конфигурации очереди сообщений.\
Хотя класс содержит все статические функции-члены, можно создать только один объект (иначе выбрасывается исключение).\
В отдельном потоке запускается запись сообщений в лог-файл и отправка сообщений в монитор.\
\
Объект не является копируемым и перемещаемым (содержит мьютекс).
### Деструктор:
Уведомляет отдельный поток логирования о завершении работы и ожидает его окончания.
```cpp
~Logger()
        {
            //Уведомить отдельный поток логирования о завершении работы
            stopLogger.store(true);

            //Вывести отдельный поток логирования из ожидания
            pushMessage = true;
            cvPushMessage.notify_one();

            //Ждать окончания работы отдельного потока логирования
            resultOfWriteToFileAndMonitor.wait();
        }
```
Необходим для корректного завершения работы, чтобы все сообщения были записаны в лог-файл и отправлены в очередь сообщений для вывода на консоль.
\
### Наиболее важные (ответственные) закрытые функции-члены логирования сообщений:

### Общедоступные функции-члены:
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
    //...
    //Получить путь файлов настроек (сonfigLoggerFilePath, configWriterMessageFilePath)
    //...

    //Создать объект логирования событий
    kav::Logger logger(сonfigLoggerFilePath, configWriterMessageFilePath);

    //...
    //Получить сообщение уровня debug (message)
    //...

    //Записать сообщение уровня debug
    Logger::debug(message);

    //...
    //Получить сообщение уровня debug (message)
    //Получить исключение (exception)
    //...

    //Записать сообщение уровня debug вместе с исключением
    Logger::debug(message, exception);

    //...
    //Аналогично используются функции записи сообщений других уровней
    //(information, warning, error, fatal) 
    //...
}
```

