# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Тесты






Класс организует взаимодействие между другими классами. Выполняет общую логику определения релевантности запросов по документам.
### Выполняет следующие функции:
1. Создаёт и хранит объекты классов ConverterJSON, Documents, InvertedIndex, Requests, RelevantResponse.
2. Рассчитывает релевантность ответов.
3. Рассчитывает релевантность ответов, при изменении документов.
4. Рассчитывает релевантность ответов, при изменении запросов.
5. Преобразует базу релевантности ответов в другой тип.
### Конструкторы:
Инициализирует объекты классов.
```cpp
SearchEngine(const JSON& in_configJSON, const JSON& in_requestsJSON)
    : converterJSONObj(in_configJSON, in_requestsJSON),
      documentsObj{},
      invertedIndexObj(documentsObj.getDocuments()),
      requestsObj{},
      relevantResponseObj(invertedIndexObj.getInvertedIndexes(), requestsObj.getRequests())
```
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
#### Преобразовать базу релевантности ответов в другой тип:
```cpp
std::vector<std::vector<std::pair<std::uint64_t, float>>> exportRelevantResponses();
```
Возвращаемое значение: база релевантности ответов
### Примеры
```cpp
#include "searchEngine.h"
#include "general.h"

int main()
{
    //Создать объект
    SearchEngine searchEngine;
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

    //Преобразовать базу релевантности ответов в другой тип
    std::vector<std::vector<std::pair<std::uint64_t, float>>> baseOfRelevantResponses{searchEngine.exportRelevantResponses()};
}
```

