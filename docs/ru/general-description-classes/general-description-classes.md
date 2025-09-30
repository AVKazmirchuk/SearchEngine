# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Общее описание классов
Общую схему интерфейсов классов можно взять здесь: (<a id="raw-url" href="https://raw.githubusercontent.com/AVKazmirchuk/SearchEngine/master/general-scheme1.png">Общая схема интерфейсов 1</a>), (<a id="raw-url" href="https://raw.githubusercontent.com/AVKazmirchuk/SearchEngine/master/general-scheme2.png">Общая схема интерфейсов 2</a>)

### В программе используются следующие классы:

#### 1. ConverterJSON
Класс реализует работу с JSON-объектами.
#### 2. Documents
Класс реализует загрузку и хранение базы документов.
#### 3. InvertedIndex
Класс реализует инвертированную индексацию документов.
#### 4. Requests
Класс реализует загрузку и хранение базы запросов.
#### 5. RelevantResponse
Класс определяет релевантность ответов.
#### 5.1 PreparedRequest (закрытый вложенный класс RelevantResponse)
Класс подготавливает базу запросов и хранит её.
#### 6. ReadTextFile
Класс реализует чтение текстовых файлов.
#### 7. ReadWriteJSONFile
Класс реализует чтение и запись JSON-файлов.
#### 8. SearchEngine
Класс организует взаимодействие между другими классами.
#### 9. CheckFile
Класс реализует проверку файла и его содержимого.
#### 10. Logger
Класс реализует логирование событий в лог-файлы и в консоль (запускается как независимое приложение).
#### 11. MonitorSender
Класс реализует отправку событий другому процессу.
#### 12. MonitorReceiver
Класс реализует получение событий от другого процесса.
#### 13. CheckFileException
Класс реализует создание исключения.\
\
&emsp;Каждый класс спроектирован как независимый от других классов. Конечно же, при создании объекта или вызова функции требуются входные данные, которые могут быть предоставлены разными интерфейсами.

### Классы можно разделить по типу применения:
#### Основные классы:
ConverterJSON, Documents, InvertedIndex, Requests, RelevantResponse, PreparedRequest
#### Вспомогательные классы:
ReadTextFile, ReadWriteJSONFile, CheckFile, Logger, MonitorSender, MonitorReceiver, CheckFileException
#### Класс управления общей логикой:
SearchEngine


