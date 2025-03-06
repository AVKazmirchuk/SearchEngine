# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс RelevantResponse
Класс определяет релевантность ответов.\
Содержит закрытый класс [PreparedRequest](./PreparedRequest/PreparedRequest.md).
### Выполняет следующие функции:
1. Очищает базу релевантности ответов.
2. Обновляет подготовленную базу запросов.
3. Рассчитывает частоту вхождения слова в документах по запросам и максимальную релевантность.
4. Определяет относительную релевантность.
5. Сортирует документы по убыванию релевантности.
6. Хранит базу релевантных ответов.
7. Предоставляет ссылку на базу релевантных ответов.
### Конструкторы:
Инициализирует: ссылку на базу инвертированных индексов, cсылку на базу запросов, объект класса PreparedRequests, ссылку на подготовленную базу запросов.
```cpp
RelevantResponse(const std::map<std::string, std::vector<Entry>>& in_invertedIndexes,
                 const std::vector<std::string>& in_requests)
    : invertedIndexes{in_invertedIndexes},
      requests{in_requests},
      preparedRequestObj{in_invertedIndexes, in_requests},
      preparedRequests{preparedRequestObj.getPreparedRequests()}
    {}
```
Оператор присваивания неявно удалён (содержит ссылки на базы).\
Копирование - затратная операция.
### Общедоступные функции-члены:\
Рассчитать релевантность ответов:
```cpp
void updateRelevantResponses();
```
Получить ссылку на базу релевантности ответов:
```cpp
const std::vector<std::vector<RelativeIndex>>& getRelevantResponses();
```
### Примеры
```cpp
#include "relevantResponse.h"

int main()
{
    //...
    //Получить ссылку на базу инвертированных индексов, cсылку на базу запросов (in_invertedIndexes, in_requests)
    //...

    //Создать объект класса RelevantResponse
    RelevantResponse relevantResponseObj(in_invertedIndexes, in_requests);
    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();
    //Получить ссылку на базу релевантности ответов
    const std::vector<std::vector<RelativeIndex>>& relevantResponses{relevantResponseObj.getRelevantResponses()};
}
```
