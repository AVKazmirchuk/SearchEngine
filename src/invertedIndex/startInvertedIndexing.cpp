//
// Created by Alexander on 22.02.2025.
//



#include "invertedIndex.h"
#include "timer.h"

#include "kav/logger.h"



void InvertedIndex::addWord(const std::string& word, std::size_t docID, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread)
{
    //Установить защиту на поиск и добавление слова в базе инвертированных индексов
    //std::unique_lock<std::mutex> lgAddWord(mutexFindAddWord);

    //Найти слово в базе инвертированных индексов
    auto positionWord{invertedIndexesForThread.find(word)};

    //Слово в базе инвертированных индексов не существует
    if (positionWord == invertedIndexesForThread.end())
    {
        //Добавить слово со структурой инвертированного индекса в базу инвертированных индексов
        invertedIndexesForThread.emplace(word, std::vector<Entry>{{docID, 1}});
    }
    else
        //Закомментированный код ниже в блоке применим для использования мьютексов. Без их применения он избыточен
        //Слово в базе инвертированных индексов существует
    /*{
        //Снять защиту на поиск и добавление слова в базе инвертированных индексов
        //lgAddWord.unlock();
        //Установить защиту на поиск и добавление структуры инвертированного индекса
        //std::unique_lock<std::mutex> lgAddEntry(mutexFindAddEntry);

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
            invertedIndexesForThread[word].push_back({docID, 1});
        }
    }*/

    //Слово в базе инвертированных индексов существует
    {
        //ID документа нового и существующего слов равно. Достаточно проверить последнюю структуру инвертированного индекса
        //в контейнере
        if (positionWord->second.back().docID == docID)
        {
            //Увеличить количество вхождений слова в документе
            ++positionWord->second.back().count;
        }
        else
            //ID документа нового и существующего слов не равно
        {
            //Добавить структуру инвертированного индекса для нового ID документа по слову
            positionWord->second.push_back({docID, 1});
        }
    }




    /*
    //Установить защиту на поиск и добавление слова в базе инвертированных индексов
    //std::unique_lock<std::mutex> lgAddWord(mutexFindAddWord);

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
        //lgAddWord.unlock();
        //Установить защиту на поиск и добавление структуры инвертированного индекса
        //std::unique_lock<std::mutex> lgAddEntry(mutexFindAddEntry);

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
    }*/
}

void InvertedIndex::defineWord(std::size_t docID, const std::string& document, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread)
{
    //Разделители слов
    const std::string  delims(" ");
    //Начальный и конечный (за последним символом) индексы слова
    std::string::size_type begIdx, endIdx;

    //Искать начало первого слова
    begIdx = document.find_first_not_of(delims);

    //Искать начало первого слова
    while (begIdx != std::string::npos)
    {
        //Искать конец текущего слова
        endIdx = document.find_first_of(delims, begIdx);

        //Конец слова равен концу строки
        if (endIdx == std::string::npos)
        {
            //Конец слова - это конец строки
            endIdx = document.length();
        }

        //Добавить слово и структуру инвертированного индекса в базу инвертированных индексов
        addWord(std::string(document, begIdx, endIdx - begIdx), docID, invertedIndexesForThread);

        //Искать начало следующего слова
        begIdx = document.find_first_not_of(delims, endIdx);
    }
}

void InvertedIndex::startInvertedIndexing(const int desiredNumberOfThreads)
{
    //Timer test
    Timer t;

    //Количество дополнительных потоков
    //Если количество документов меньше желаемого количества потоков - использовать количество потоков равным количеству документов.
    //В противном случае - использовать желаемое количество документов.
    int numberOfThreads = documents.size() <= desiredNumberOfThreads ? documents.size() : desiredNumberOfThreads;

    //Определить количество документов обрабатываемое одним потокам
    std::size_t difference{documents.size() / numberOfThreads};

    //Если количество документов делится с остатком
    if (documents.size() % numberOfThreads)
    {
        //Увеличить количество потоков
        ++numberOfThreads;
    }

    //Контейнер результатов потоков
    std::list<std::future<std::map<std::string, std::vector<Entry>>>> futures(numberOfThreads);

    //ID первого документа для каждого потока
    std::size_t beginDocID{};

    //Для каждого будущего потока
    for (auto &future : futures)
    {
        //ID последнего документа для каждого потока
        std::size_t endDocID{beginDocID + difference - 1};

        //Если ID последнего документа для потока превышает ID документа всех документов
        if (endDocID >= documents.size())
        {
            //Установить ID последнего документа для потока равным ID последнего документа всех документов
            endDocID = documents.size() - 1;
        }

        //std::cout << "beginDocID: " << beginDocID << ", endDocID: " << endDocID << '\n';

        //Запустить чтение файлов в отдельном потоке в своём диапазоне
        future = std::async([this, beginDocID, endDocID]()
                            {
                                //База инвертированных индексов для каждого потока
                                std::map<std::string, std::vector<Entry>> invertedIndexesForThread;

                                //Для каждого документа
                                for (std::size_t currentDocID{beginDocID}; currentDocID <= endDocID; ++currentDocID)
                                {
                                    //Определить слово (выделить) в документе
                                    InvertedIndex::defineWord(currentDocID, documents[currentDocID], invertedIndexesForThread);
                                }

                                return invertedIndexesForThread;
                            }
        );

        //Определить ID первого документа для следующего потока
        beginDocID = endDocID + 1;
    }

    try
    {
        //Ожидать завершения потоков
        for (auto &future: futures)
        {
            //InvertedIndex::invertedIndexesForThread = future.get();

            for (auto &elem : future.get())
            {
                //Найти слово в базе инвертированных индексов
                auto positionWord{invertedIndexes.find(elem.first)};

                //Слово в базе инвертированных индексов не существует
                if (positionWord == invertedIndexes.end())
                {
                    //Добавить слово c контейнером структур инвертированного индекса в базу инвертированных индексов
                    invertedIndexes.emplace(elem.first, elem.second);
                }
                else
                    //Слово в базе инвертированных индексов существует
                {
                    for (auto &entry : elem.second)
                    {
                        //Добавить структуру инвертированного индекса для нового ID документа по слову
                        invertedIndexes[elem.first].push_back(entry);
                    }
                }
            }
        }
    }
    //Обработать все исключения, выброшенные в потоках
    catch (const std::exception& e)
    {
        throw;
    }

    std::cout << '\n' << "numberOfThreads: " << numberOfThreads << '\n';
    std::cout << '\n' << t.elapsed() << '\n';


    /*for (std::size_t docID{}; docID < documents.size(); ++docID)
    {

        InvertedIndex::defineWord(docID, documents[docID]);
    }

    std::cout << '\n' << t.elapsed() << '\n';*/
}