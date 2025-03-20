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
6. Хранит базу релевантности ответов.
7. Предоставляет ссылку на базу релевантности ответов.
### Релевантность ответов
Программа использует относительную индексацию для подсчёта встречаемости слова из запроса в документе. Относительный индекс - это список структур (в программе используется структура RelativeIndex), соответствующий каждому запросу для поиска. Сама структура представляет два поля: идентификатор документа и ранг. Ранг - это сумма всех вхождений слов из одного запроса в документе делёная на максимальное значение сумм всех вхождений слов из каждого запроса в документе. Набор запросов и соответствующих списков таких структур представляет базу релевантности ответов. По этой базе осуществляется вывод результатов поиска в удобочитаемом виде.  
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
### Общедоступные функции-члены:
#### Рассчитать релевантность ответов:
```cpp
void updateRelevantResponses();
```
#### Получить ссылку на базу релевантности ответов:
```cpp
const std::vector<std::vector<RelativeIndex>>& getRelevantResponses();
```
Возвращаемое значение: ссылка на базу релевантности ответов
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
