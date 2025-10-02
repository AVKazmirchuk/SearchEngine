# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

Программа Logger Monitor (logger_monitor.exe) выводит сообщения на консоль. Сообщения получает из очереди сообщений, основанной на оригинальной очереди boost::interprocess::message_queue.\
Работа зависит от запускаемого файла с библиотекой kav::logger, так как сообщения читаются именно из очереди поступившие из этой библиотеки.\
Используется основной класс kav::LoggerMonitor и вспомогательный закрытый класс kav::ConfigLoggerMonitor. Вспомогательный класс подробно описываться не будет. В исходных файлах есть все необходимые комментарии, а так же приведена элементарная логика работы на схеме.

## Класс LoggerMonitor
Класс реализует вывод сообщений на консоль.
### Выполняет следующие функции:
1. Читает сообщения из очереди сообщений.
2. Выводит полученные сообщения на консоль в разных цветах согласно уровню логирования каждого сообщения.

Для настройки класса используется файл конфигураци: messageQueue.json.\
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
Параметры: файл конфигурации монитора.
Объект является копируемым (неявно) и перемещаемым (неявно).
### Общедоступные функции-члены:
#### Проверить файл на целостность JSON-структуры:
```cpp
static bool isJSONStructureValid(const std::string &fileName);
```
Параметры: ссылка на имя файла
Возвращаемое значение: целостность JSON-структуры 
#### Проверить JSON-структуру файла на соответствие шаблону:
```cpp
static bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);
```
Параметры: ссылка на проверяемый JSON-объект, ссылка на JSON-объект шаблона
Возвращаемое значение: соотвествие JSON-структуры шаблону
### Примеры
```cpp
#include "checkFile.h"

int main()
{
    //...
    //Получить имя файла (fileName)
    //...
    
    //Проверить файл на целостность JSON-структуры
    bool JSONStructureValid{CheckFile::isJSONStructureValid(fileName)};

    //...
    //Получить JSON-объекты шаблона и проверяемого (objectJSONTemplate, objectJSON)
    //...

    //Проверить JSON-структуру файла на соответствие шаблону
    bool JSONStructureMatch{CheckFile::isJSONStructureMatch(objectJSONTemplate, objectJSON)};
}
```
