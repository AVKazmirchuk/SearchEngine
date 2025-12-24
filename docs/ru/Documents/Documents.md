# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс Documents
Класс реализует загрузку и хранение базы документов.
### Выполняет следующие функции:
1. Обновляет базу документов.
2. Хранит базу документов или путей файлов документов.
3. Предоставляет ссылку на базу документов или путей файлов документов.
4. Очищает базу документов или путей файлов документов.
### Конструкторы:
```cpp
Documents() = default;
```
Объект является копируемым (неявно) и перемещаемым (неявно).\
Копирование - затратная операция.
### Общедоступные функции-члены:
#### Обновить базу документов:
```cpp
void updateDocuments(const std::vector<std::string>& in_documents);
void updateDocuments(std::vector<std::string>&& in_documents);
```
Параметры: база документов
#### Получить ссылку на базу документов:
```cpp
const std::vector<std::string>& getDocuments();
```
Возвращаемое значение: ссылка на базу документов
#### Очистить базу документов:
```cpp
void clearDocuments();
```
### Примеры
```cpp
#include "documents.h"

int main()
{
    //Создать объект класса Documents
    Documents documentsObj;

    //...
    //Получить базу документов (in_documents)
    //...

    //Обновить базу документов
    documentsObj.updateDocuments(in_documents);
    //Получить ссылку на базу документов
    const std::vector<std::string>& documents{documentsObj.getDocuments()};
    //Очистить базу документов
    documentsObj.clearDocuments();
}
```
