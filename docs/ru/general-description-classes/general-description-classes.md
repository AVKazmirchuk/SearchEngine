# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Общее описание классов
Общую схему интерфейсов классов можно взять здесь: (<a id="raw-url" href="https://raw.githubusercontent.com/AVKazmirchuk/SearchEngine/master/general-scheme1.png">Общая схема интерфейсов 1</a>), (<a id="raw-url" href="https://raw.githubusercontent.com/AVKazmirchuk/SearchEngine/master/general-scheme2.png">Общая схема интерфейсов 2</a>)

### В основной программе используются следующие классы:

#### 1. ConverterJSON
Класс реализует работу с JSON-объектами.
#### 1.1. ConverterJSON::ConfigConverterJSON
Класс реализует чтение и хранение параметров для настройки класса ConverterJSON
#### 2. DispatcherOperationValidity
Класс реализует диспетчер операций c файлами и JSON-объектами.
#### 3. OperationException
Класс реализует исключение.
#### 4. Documents
Класс реализует загрузку и хранение базы документов.
#### 5. InvertedIndex
Класс реализует инвертированную индексацию документов.
#### 6. RelevantResponse
Класс определяет релевантность ответов.
#### 6.1 RelevantResponse::PreparedRequest (закрытый класс)
Класс подготавливает базу запросов и хранит её.
#### 7. Requests
Класс реализует загрузку и хранение базы запросов.
#### 8. SearchEngine
Класс организует взаимодействие между другими классами.
\
&emsp;Каждый класс спроектирован как независимый от других классов. Конечно же, при создании объекта или вызова функции требуются входные данные, которые могут быть предоставлены разными интерфейсами.

### В библиотеке kav_check используются следующие классы:

#### 1. kav::CheckJSON
Класс реализует проверку соответствия JSON-структуры шаблону.
#### 2. kav::OperationFileAndJSON
Класс реализует чтение и запись файлов с проверкой, а также проверку JSON-объектов.

### В библиотеке kav_logger используются следующие классы:

#### 1. kav::LoggerException
Класс реализует исключение.
#### 2. kav::Logger
Класс реализует логирование событий.
#### 2.1. kav::Logger::ConfigLogger (закрытый класс)
Класс реализует чтение и хранение параметров для настройки класса Logger.
#### 2.2. kav::Logger::WriterMessage (закрытый класс)
Класс реализует запись сообщений в лог-файл и монитор.
#### 2.2.1. kav::Logger::WriterMessage::ConfigWriterMessage (закрытый класс)
Класс реализует чтение и хранение параметров для настройки класса WriterMessage, MonitorSender.
#### 2.3. kav::Logger::ExceptionStub (закрытый класс)
Класс реализует иключение-заглушку
#### 2.4. kav::Logger::OnlyOneObject (закрытый класс)
Класс реализует исключение о невозможности создания более одного объекта.
#### 3. kav::MonitorSender
Класс отправки сообщений для вывода на монитор.
#### 3.1 kav::MonitorSender::RemoveMessageQueue (закрытый класс)
Класс реализует удаление оставшейся очереди сообщений (во избежание ошибок) перед инициализацией очереди.

### В программе logger_monitor используются следующие классы:

#### 1. kav::LoggerMonitor
Класс реализует логирование событий в монитор.
#### 1.1. kav::LoggerMonitor::ConfigLoggerMonitor (закрытый класс)
Класс реализует чтение и хранение параметров для настройки классов LoggerMonitor, MonitorReceiver.
#### 2. kav::MonitorReceiver
Класс реализует получение сообщений для вывода на монитор.
#### 2.1. kav::MonitorReceiver::RemoveMessageQueue (закрытый класс)
Класс реализует удаление оставшейся очереди сообщений (во избежание ошибок) перед инициализацией очереди.

### Классы основной программы можно разделить по типу применения:
#### Основные классы:
ConverterJSON, Documents, InvertedIndex, Requests, RelevantResponse, PreparedRequest
#### Вспомогательные классы:
DispatcherOperationValidity, OperationException
#### Класс управления общей логикой:
SearchEngine


