# SearchEngine
Документация SearchEngine

### [Класс RelevantResponse](../RelevantResponse.md)

## Класс PreparedRequest
Класс подготавливает базу запросов и хранит её.
### Выполняет следующие функции:
1. Очищает подготовленную базу запросов.
2. Разбивает базу запросов на отдельные слова и заполняет ими подготовленную базу запросов.
3. Преобразует подготовленные запросы, в запросы, содержащие уникальные слова.
4. Сортирует слова по частоте вхождения в документы.
5. Хранит подготовленную базу запросов.
6. Предоставляет ссылку на подготовленную базу запросов.
### Конструкторы:
Инициализирует: ссылку на базу инвертированных индексов, ссылку на базу запросов.
```cpp
PreparedRequest(const std::map<std::string, std::vector<Entry>>& in_invertedIndexes,
                const std::vector<std::string>& in_requests)
       : invertedIndexes{in_invertedIndexes},
         requests{in_requests}
        {}
```
Параметры: ссылка на базу инвертированных индексов, ссылка на базу запросов.\
Оператор присваивания неявно удалён (содержит ссылки на базы).\
Копирование - затратная операция.
### Общедоступные функции-члены:
#### Обновить подготовленную базу запросов:
```cpp
void updatePreparedRequests();
```
#### Получить ссылку на подготовленную базу запросов:
```cpp
const std::vector<std::vector<std::string>>& getPreparedRequests();
```
Возвращаемое значение: ссылка на подготовленную базу запросов
### Примеры
```cpp
#include "preparedRequest.h"

int main()
{
    //...
    //Получить ссылку на базу инвертированных индексов, cсылку на базу запросов (in_invertedIndexes, in_requests)
    //...

    //Создать объект класса PreparedRequest
    RelevantResponse preparedRequestObj(in_invertedIndexes, in_requests);
    //Обновить подготовленную базу запросов
    relevantResponseObj.updatePreparedRequests();
    //Получить ссылку на подготовленную базу запросов
    const std::vector<std::vector<std::string>>& preparedRequests{preparedRequestObj.getPreparedRequests()};
```
