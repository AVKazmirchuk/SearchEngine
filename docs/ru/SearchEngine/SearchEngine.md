# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс SearchEngine
Класс организует взаимодействие между другими классами. Выполняет общую логику определения релевантности запросов по документам\
\
&emsp;&emsp###;Выполняет следующие функции:
		
1. Создаёт и хранит объекты классов ConverterJSON, Documents, InvertedIndex, Requests, RelevantResponse
2. Рассчитывает релевантность ответов
3. Рассчитывает релевантность ответов, при изменении документов
4. Рассчитывает релевантность ответов, при изменении запросов
5. Преобразует базу релевантности ответов в другой тип\
\
&emsp;###Конструкторы:
```cpp
SearchEngine()
    : converterJSONObj(ReadWriteJSONFile().readJSONFile(constants::configFilePath),
                       ReadWriteJSONFile().readJSONFile(constants::requestsFilePath)),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())
    {}
```
Инициализирует объекты классов\
\
&emsp;Не является копируемым и перемещаемым (содержит объект InvertedIndex (содержит мьютекс))\
\
&emsp;###Общедоступные функции-члены:\
Рассчитать релевантность ответов:
```cpp
void searchModifiedAll();
```
Рассчитать релевантность ответов, при изменении документов:
```cpp
void searchModifiedDocuments();
```
Рассчитать релевантность ответов, при изменении запросов
```cpp
void searchModifiedRequests();
```
Преобразовать базу релевантности ответов в другой тип:
```cpp
std::vector<std::vector<std::pair<int, float>>> exportRelevantResponses();
```
  
