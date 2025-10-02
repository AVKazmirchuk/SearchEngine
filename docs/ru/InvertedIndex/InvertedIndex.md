# SearchEngine
Документация SearchEngine

### [Оглавление](../index.md)

## Класс InvertedIndex
Класс реализует инвертированную индексацию документов.
### Выполняет следующие функции:
1. Очищает базу инвертированных индексов.
2. Запускает инвертированную индексацию документов в отдельных потоках.
3. Хранит базу инвертированных индексов.
4. Предоставляет ссылку на базу инвертированных индексов.
### Инвертированный индекс
Программа использует инвертированную индексацию для подсчёта встречаемости слов в документах. Инвертированный индекс - это список структур (в программе используется структура Entry), соответствующий каждому слову в базе документов. Сама структура представляет два поля: идентификатор документа и количество вхождений слова в этом документе. Набор слов и соответствующих списков таких структур представляет базу инвертированных индексов.\
Пример. Два документа состоят из слов: {milk milk milk lemon water water water}, {milk milk lemon milk milk water water lemon water water}.\
База будет представлять следующее:
| Слово | Entry  | Entry  |
|-------|--------|--------|
| lemon | {0, 1} | {1, 2} |
| milk  | {0, 3} | {1, 4} |
| water | {0, 3} | {1, 4} |

По этой базе осуществляется поиск по запросам.
### Конструкторы:
Инициализирует ссылку на базу документов.
```cpp
explicit InvertedIndex(const std::vector<std::string>& in_documents) : documents{in_documents} {}
```
Параметры: ссылка на базу документов.
\
Не является копируемым и перемещаемым (содержит мьютекс).
### Наиболее важные (интересные) закрытые функции-члены индексации документов:
Ниже представлена функция запускающая инвертированную индексацию документов в отдельных потоках:
```cpp
void InvertedIndex::startInvertedIndexing()
{
    //Контейнер результатов потоков
    std::list<std::future<void>> futures;

    //Запустить потоки
    for (std::size_t docID{}; docID < documents.size(); ++docID)
    {
        //Запустить поток для определения слова (выделения) в документе
        futures.push_back(std::async(&InvertedIndex::defineWord, this, docID, std::cref(documents[docID])));
    }

    try
    {
        //Ожидать завершения потоков
        for (auto &future: futures)
            future.wait();
    }
    //Обработать все исключения, выброшенные в потоках
    catch (const std::exception& e)
    {
        throw;
    }
}
```
Как видно, функция запускает функцию "void InvertedIndex::defineWord(std::size_t docID, const std::string& document)" в отдельных потоках для каждого документа.\
В свою очередь она запускает функцию "void InvertedIndex::addWord(const std::string& word, std::size_t docID)" для добавления слова и структуру инвертированного индекса в базу инвертированных индексов:
```cpp
void InvertedIndex::addWord(const std::string& word, std::size_t docID)
{
    //Установить защиту на поиск и добавление слова в базе инвертированных индексов
    std::unique_lock<std::mutex> lgAddWord(mutexFindAddWord);

    //Найти слово в базе инвертированных индексов
    auto positionWord{invertedIndexes.find(word)};

    //Слово в базе инвертированных индексов не существует
    if (positionWord == invertedIndexes.end())
    {
        //Добавить слово со структурой инвертированного индекса в базу инвертированных индексов
        invertedIndexes.emplace(word, std::vector<Entry>{{docID, 1}});
    }
    else
        //Слово в базе инвертированных индексов существует
    {
        //Снять защиту на поиск и добавление слова в базе инвертированных индексов
        lgAddWord.unlock();
        //Установить защиту на поиск и добавление структуры инвертированного индекса
        std::unique_lock<std::mutex> lgAddEntry(mutexFindAddEntry);

        //Найти структуру инвертированного индекса с равным ID документа нового и существующего слов
        auto positionDocId{std::find_if(positionWord->second.begin(), positionWord->second.end(),
                                        [docID = docID](const Entry& entry)
                                        {
                                            return entry.docID == docID;
                                        })};
        //ID документа нового и существующего слов равно
        if (positionDocId != positionWord->second.end())
        {
            //Увеличить количество вхождений слова в документе
            ++positionDocId->count;
        }
        else
            //ID документа нового и существующего слов не равно
        {
            //Добавить структуру инвертированного индекса для нового ID документа по слову
            invertedIndexes[word].push_back({docID, 1});
        }
    }
}
```
Как видно, добавление слова и структуры инвертированного индекса в базу для разных потоков защищается двумя мьютексами:
- InvertedIndex::mutexFindAddWord: мьютекс на поиск и добавление слова;
- InvertedIndex::mutexFindAddEntry: мьютекс на поиск и добавление структуры инвертированного индекса.

Алгоритм поиска и добавления слов и структур из комментариев очевиден, и не требует особых пояснений.

### Общедоступные функции-члены:
#### Обновить базу инвертированных индексов:
```cpp
void updateInvertedIndexes();
```
#### Получить ссылку на базу инвертированных индексов:
```cpp
const std::map<std::string, std::vector<Entry>>& getInvertedIndexes();
```
Возвращаемое значение: ссылка на базу инвертированных индексов
### Примеры
```cpp
#include "invertedIndex.h"

int main()
{
    //...
    //Получить ссылку на базу документов (in_documents)
    //

    //Создать объект класса InvertedIndex
    InvertedIndex invertedIndexObj(in_documents);
    //Обновить базу инвертированных индексов
    invertedIndexObj.updateInvertedIndexes();
    //Получить ссылку на базу инвертированных индексов
    const std::map<std::string, std::vector<Entry>>& invertedIndexes{invertedIndexObj.getInvertedIndexes()};
}
```
