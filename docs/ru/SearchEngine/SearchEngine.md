# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс SearchEngine
Класс организует взаимодействие между другими классами. Выполняет общую логику определения релевантности запросов по документам.
### Выполняет следующие функции:
1. Создаёт и хранит объекты классов ConverterJSON, Documents, InvertedIndex, Requests, RelevantResponse.
2. Рассчитывает релевантность ответов.
3. Рассчитывает релевантность ответов, при изменении документов.
4. Рассчитывает релевантность ответов, при изменении запросов.
5. Преобразует базу релевантности ответов в другой тип.
### Конструкторы:
Инициализирует объекты всех классов.
```cpp
SearchEngine(const std::string& in_configFilePath, const std::string& in_requestsFilePath, const std::string& in_answersFilePath, int in_precision, int in_formatByWidth)
    : converterJSONObj(in_configFilePath, in_requestsFilePath, in_precision),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests(), in_precision),
      answersFilePath{in_answersFilePath}, formatByWidth{in_formatByWidth}
```
Параметры: ссылка на путь файла конфигурации, ссылка на путь файла запросов, ссылка на путь файла ответов, количество знаков после запятой, ширина вывода, желаемое количество потоков, 
максимальное количество непрочитанных файлов (допустимых ошибок).\
Объект не является копируемым и перемещаемым (содержит объект класса InvertedIndex (содержит мьютекс)).
### Общедоступные функции-члены:
#### Рассчитать релевантность ответов:
```cpp
void searchModifiedAll();
```
#### Рассчитать релевантность ответов, при изменении документов:
```cpp
void searchModifiedDocuments();
```
#### Рассчитать релевантность ответов, при изменении запросов:
```cpp
void searchModifiedRequests();
```
### Примеры
```cpp
#include "searchEngine.h"

int main()
{
    //Получить ссылки на путь файла конфигурации (configFilePath), запросов (requestsFilePath), ответов (answersFilePath); получить количество знаков после запятой (precision), ширину вывода (formatByWidth),
желаемое количество потоков (desiredNumberOfThreads), максимальное количество непрочитанных файлов (maximumAllowableErrorsNumber)


    //Создать объект
    SearchEngine searchEngine(configFilePath, requestsFilePath, answersFilePath, precision, formatByWidth, desiredNumberOfThreads, maximumAllowableErrorsNumber);
    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();

    //...
    //Изменение документов
    //...

    //Рассчитать релевантность ответов, при изменении документов
    searchEngine.searchModifiedDocuments();

    //...
    //Изменение запросов
    //...

    //Рассчитать релевантность ответов, при изменении запросов
    searchEngine.searchModifiedRequests();

    //...
    //Изменение документов и запросов
    //...

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();
}
```
