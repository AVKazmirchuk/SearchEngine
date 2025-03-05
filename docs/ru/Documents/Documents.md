# SearchEngine
Документация SearchEngine на русском

### [Оглавление](../index.md)

## Класс Documents
Класс реализует загрузку и хранение базы документов\
\
&emsp;&emsp;Выполняет следующие функции:
		
1. Обновляет базу документов.
2. Хранит базу документов.
3. Предоставляет ссылку на базу документов.
4. Очищает базу документов.\
\
&emsp;Конструкторы:\
По умолчанию\
\
&emsp;Является: копируемым (неявно) и перемещаемым (неявно)\
\
Копирование - затратная операция\

&emsp;Общедоступные функции-члены:\
Обновить базу документов:\
&emsp;void updateDocuments(const std::vector<std::string>& in_documents);\
&emsp;void updateDocuments(std::vector<std::string>&& in_documents);\
Получить ссылку на базу документов\
&emsp;const std::vector<std::string>& getDocuments();\
Очистить базу документов\
&emsp;clearDocuments();
