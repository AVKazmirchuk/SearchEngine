
# SearchEngine
Документация SearchEngine на русском

### [Оглавление](../index.md)

## Класс Requests
Класс реализует загрузку и хранение базы запросов\
\
&emsp;&emsp;Выполняет следующие функции:
		
1. Обновляет базу запросов.
2. Хранит базу запросов.
3. Предоставляет ссылку на базу запросов.
4. Очищает базу запросов.\
\
&emsp;Конструкторы:\
По умолчанию\
\
&emsp;Является: копируемым (неявно) и перемещаемым (неявно)\
\
Копирование - затратная операция
\
&emsp;Общедоступные функции-члены:\
Обновить базу запросов:\
&emsp;void updateRequests(const std::vector<std::string>& in_requests);\
&emsp;void updateRequests(std::vector<std::string>&& in_requests);\
Получить ссылку на базу запросов\
&emsp;const std::vector<std::string>& getRequests();\
Очистить базу запросов\
&emsp;void clearRequests();
