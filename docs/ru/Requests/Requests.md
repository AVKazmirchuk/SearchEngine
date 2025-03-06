
# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс Requests
Класс реализует загрузку и хранение базы запросов.
### Выполняет следующие функции:
1. Обновляет базу запросов.
2. Хранит базу запросов.
3. Предоставляет ссылку на базу запросов.
4. Очищает базу запросов.
### Конструкторы:
```cpp
Requests() = default;
```
Является копируемым (неявно) и перемещаемым (неявно).\
Копирование - затратная операция.
### Общедоступные функции-члены:
Обновить базу запросов:
```cpp
void updateRequests(const std::vector<std::string>& in_requests);
void updateRequests(std::vector<std::string>&& in_requests);
```
Получить ссылку на базу запросов:
```cpp
const std::vector<std::string>& getRequests();
```
Очистить базу запросов:
```cpp
void clearRequests();
```
