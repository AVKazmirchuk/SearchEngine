# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

Программа Logger Monitor (logger_monitor.exe) выводит сообщения на консоль. Сообщения получает из очереди сообщений, основанной на оригинальной очереди boost::interprocess::message_queue.\
Работа зависит от запускаемого файла с библиотекой kav::logger, так как сообщения читаются именно из очереди поступившие из этой библиотеки.\
Используется основной класс kav::LoggerMonitor и вспомогательный закрытый класс kav::ConfigLoggerMonitor. Вспомогательный класс подробно описываться не будет. В исходных файлах есть все необходимые комментарии, а так же приведена элементарная логика работы на схеме.

## Класс LoggerMonitor
Класс реализует вывод сообщений на консоль.\
Для настройки класса используется файл конфигураци: messageQueue.json.
### Выполняет следующие функции:
1. Читает сообщения из очереди сообщений.
2. Выводит полученные сообщения на консоль в разных цветах согласно уровню логирования каждого сообщения.

### Файлы конфигурации
Класс использует файл конфигурации (messageQueue.json) для настройки очереди сообщений.\
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
```cpp
explicit LoggerMonitor(const std::string &in_configLoggerMonitorFilePath)
                : configLoggerMonitor(in_configLoggerMonitorFilePath),
                  monitorReceiver(configLoggerMonitor.nameOfQueue(),
                                  configLoggerMonitor.maxNumberOfMessages(),
                                  configLoggerMonitor.maxMessageSize(),
                                  configLoggerMonitor.fileNameOfMainProgram())
        {
            //Добавить в контейнер имя очереди
            queuesInUse.push_back(configLoggerMonitor.nameOfQueue());

            //TODO Зачем поставил это условие - не помню
            if (queuesInUse.size() == 1)
            {
                //Зарегистрировать обработчик нажатия клавиш консоли
                SetConsoleCtrlHandler(&ConsoleCtrlEventHandler, TRUE);
            }
        }
```
Создаёт объект классов СonfigLoggerMonitor и monitorReceiver.\
Параметры: файл конфигурации монитора.\
Объект является копируемым (неявно) и перемещаемым (неявно).
### Наиболее важные (интересные) закрытые функции-члены обработки сообщений:
Следует обратить внимание, что в обработчике событий консоли прописана функция "static void stop()", которая при закрытии консоли записывает в очередь сообщение: nameOfQueue + "Stop". Это сообщение отслеживается в функции "void run()", и при его появлении в очереди обработка сообщений завершается. Это сделано на будущее.
### Класс kav::MonitorReceiver:
Представляет собой класс-обёртку получения сообщений для вывода на монитор над оригинальным классом boost::interprocess::message_queue. Будет описан кратко, так как класс небольшой и его функциональность вполне очевидно описана в комментариях.\
Назачение:\
Открывает или создаёт очередь сообщений. Создаёт объекты: RemoveMessageQueue, boost::interprocess::message_queue. Если процесс получения и вывода сообщений запущен, - значит очередь сообщений существует, - открыть очередь сообщений. Если процесс получения и вывода сообщений не запущен, - значит очередь сообщений не существует, - создать очередь сообщений.

### Общедоступные функции-члены:
#### Запустить монитор:
```cpp
void run();
```
### Примеры
```cpp
#include "monitor.h"

int main()
{
    //...
    //Получить файл конфигурации монитора (configLoggerMonitorFilePath)
    //...
    
    //Создать объект класса логирования событий в монитор
    kav::LoggerMonitor loggerMonitor(configLoggerMonitorFilePath);

    //Запустить монитор
    loggerMonitor.run();
}
```
