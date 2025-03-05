# SearchEngine
Документация SearchEngine на русском

### [Оглавление](../index.md)

## Класс ConverterJSON
Класс реализует работу с JSON-объектами\
\
&emsp;&emsp;Выполняет следующие функции:
		
1. Получает список файлов документов.
2. Получает запросы.
3. Получает значение максимального количества ответов.
4. Записывает в JSON-объект результаты поиска.
5. Получает JSON-объект ответов.
6. Хранит JSON-объекты конфигурации, запросов, ответов
7. Предоставляет ссылку на JSON-объект ответов\
\
&emsp;Конструкторы:\
ConverterJSON(const JSON& in_configJSON, const JSON& in_requestsJSON)\
ConverterJSON(JSON&& in_configJSON, JSON&& in_requestsJSON)\
\
&emsp;Является: копируемым (неявно) и перемещаемым (неявно)\
\
&emsp;Общедоступные функции-члены:\
Получить список файлов документов:\
&emsp;std::vector<std::string> getFilePaths();\
Получить запросы:\
&emsp;std::vector<std::string> getRequests();\
Получить значение максимального количества ответов\
&emsp;int getMaxResponses();\
Записать в JSON-объект результаты поиска:\
&emsp;void setAnswersJSON(const std::vector<std::vector<std::pair<int, float>>>& answers, int maxResponses);\
Получить JSON-объект ответов\
&emsp;JSON& getAnswersJSON();
