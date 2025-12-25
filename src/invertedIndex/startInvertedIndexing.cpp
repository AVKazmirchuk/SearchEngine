//
// Created by Alexander on 22.02.2025.
//



#include "DispatcherOperations.h"
#include "invertedIndex.h"
#include "timer.h"

#include "kav/logger.h"



void InvertedIndex::mergeInvertedIndexBases(std::vector<std::future<std::map<std::basic_string<char>, std::vector<Entry>>>> &futures)
{
    //Начальное количество баз инвертированного индекса для каждого потока должно быть в следующих очевидных пределах
    //Если начальное количество баз инвертированного индекса для каждого потока меньше нижнего предела - установить по нижнему пределу
    if (initialBasesNumberInStream < 2) initialBasesNumberInStream = 2;
    //Если начальное количество баз инвертированного индекса для каждого потока больше верхнего предела - установить по верхнему пределу
    else if (initialBasesNumberInStream > futures.size()) initialBasesNumberInStream = futures.size();

    //Определить индекс для записи в контейнер результатов потоков
    std::size_t i{};

    //Пока элементы в контейнере результатов потоков не закончились, и в контейнере содержатся более одного элемента
    for (std::size_t idx{}; idx < futures.size() && futures.size() != 1; idx += initialBasesNumberInStream, ++i)
    {
        //Если следующий элемент существует
        if ((idx + 1) < futures.size())
        {
            //Определить количество баз инвертированного индекса для каждого потока в зависимости от количества элементов контейнера и индекса текущего элемента
            const unsigned int basesNumberInStream = (futures.size() - idx) >= initialBasesNumberInStream ? initialBasesNumberInStream : futures.size() - idx;
            //Определить контейнер баз инвертированного индекса для потока
            std::vector<std::map<std::basic_string<char>, std::vector<Entry>>> invertedIndexesForThread(basesNumberInStream);

            //Пока элементы существуют в базе
            for (unsigned int k{}; k < basesNumberInStream; ++k)
            {
                try
                {
                    //Переместить их из контейнера результатов потоков
                    invertedIndexesForThread[k] = std::move(futures[idx + k]).get();
                }
                //Обработать выше все исключения, выброшенные в потоках
                catch (const std::exception& e)
                {
                    throw;
                }
            }

            //Записать результат в контейнер результатов потоков
            futures[i] = std::async([invertedIndexesForThread = std::move(invertedIndexesForThread)]() mutable
                                    {
                                        //Пока контейнер баз не пройден
                                        for (unsigned int l{1}; l < invertedIndexesForThread.size(); ++l)
                                        {
                                            //Для каждой базы инвертированного индекса
                                            for (auto &elem: invertedIndexesForThread[l])
                                            {
                                                //Найти слово в базе инвертированных индексов
                                                auto positionWord{invertedIndexesForThread[0].find(elem.first)};

                                                //Слово в базе инвертированных индексов не существует
                                                if (positionWord == invertedIndexesForThread[0].end())
                                                {
                                                    //Добавить слово c контейнером структур инвертированного индекса в базу инвертированных индексов
                                                    invertedIndexesForThread[0].insert(
                                                            {elem.first, std::move(elem.second)});
                                                } else
                                                    //Слово в базе инвертированных индексов существует
                                                {
                                                    //Для каждого элемента контейнера индекса
                                                    for (auto &entry: elem.second)
                                                    {
                                                        //Добавить структуру инвертированного индекса для нового ID документа по слову
                                                        invertedIndexesForThread[0][elem.first].push_back(entry);
                                                    }
                                                }
                                            }
                                        }

                                        //Вернуть базу инвертированного индекса из потока
                                        return std::move(invertedIndexesForThread[0]);
                                    }
            );

        }
        else
        {
            //Следующий элемент не существует (один элемент)
            futures[i] = std::move(futures[idx]);
        }
    }

    //Урезать размер контейнера до количества потоков
    futures.resize(i);

    //Если количество потоков более одного
    if (i > 1)
    {
        //Вызвать рекурсивно функцию
        mergeInvertedIndexBases(futures);
    }
}

void InvertedIndex::addWord(const std::string& word, std::size_t docID, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread)
{


    //Найти слово в базе инвертированных индексов
    auto positionWord{invertedIndexesForThread.find(word)};

    //Слово в базе инвертированных индексов не существует
    if (positionWord == invertedIndexesForThread.end())
    {
        //Добавить слово со структурой инвертированного индекса в базу инвертированных индексов
        invertedIndexesForThread.emplace(word, std::vector<Entry>{{docID, 1}});
    }
    else
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
    //Закомментированный код ниже в блоке применим для использования мьютексов. Без их применения он избыточен
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
        const std::string delims(" ");
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


        /**
         * Отображение файла в память
         */

        /*boost::interprocess::file_mapping fileMapping(document.c_str(), boost::interprocess::read_only);
        boost::interprocess::mapped_region mappedRegion(fileMapping, boost::interprocess::read_only);

        const char * address{static_cast<const char *>(mappedRegion.get_address())};
        std::size_t size{mappedRegion.get_size()};
        const char * addressEnd{address + size};

        std::string word;

        while (address != addressEnd)
        {
            word += *address;
            if (word.back() == ' ')
            {
                word.pop_back();

                if (!word.empty())
                {
                    addWord(word, docID, invertedIndexesForThread);

                    word.clear();
                }
            }

            ++address;
        }

        if (!word.empty())
        {
            addWord(word, docID, invertedIndexesForThread);
        }//Отображение файла в память*/

}

void InvertedIndex::readDocument(std::size_t docID, const std::string& documentPath, std::map<std::string, std::vector<Entry>>& invertedIndexesForThread)
{
     //Определить слово (выделить) в документе, предварительно прочитав файл
     defineWord(docID, DispatcherOperations::readMultipleTextFilesSequentially(documentPath, documents.size(), maximumAllowableErrorsNumber).first, invertedIndexesForThread);
}

void InvertedIndex::startInvertedIndexing()
{
    //Если используется база путей файлов документов
    if (documentsBaseOrPathsBase != Constants::default_documentsBaseOrPathsBase())
    {
        //В начале прочитать документ по его пути
        defineWordOrReadDocumentAtBeginning = &InvertedIndex::readDocument;
    }

    /**
     * Инвертированная индексация документов в отдельных потоках
     */

    //Определить количество потоков
    std::pair<std::size_t, const unsigned int> tmp{countNumberOfThreads()};

    //Количество документов обрабатываемое одним потокам
    std::size_t difference{tmp.first};

    //Определить количество дополнительных потоков
    const unsigned int numberOfThreads = tmp.second;

    //Контейнер результатов потоков
    std::vector<std::future<std::map<std::string, std::vector<Entry>>>> futures(numberOfThreads);

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

        //Запустить чтение файлов в отдельном потоке в своём диапазоне
        future = std::async([this, beginDocID = beginDocID, endDocID = endDocID]()
                            {
                                //База инвертированных индексов для каждого потока
                                std::map<std::string, std::vector<Entry>> invertedIndexesForThread;

                                //Для каждого документа
                                for (std::size_t currentDocID{beginDocID}; currentDocID <= endDocID; ++currentDocID)
                                {
                                    //Определить слово (выделить) в документе
                                    (this->*defineWordOrReadDocumentAtBeginning)(currentDocID, documents[currentDocID], invertedIndexesForThread);
                                }

                                //Вернуть базу инвертированных индексов для каждого потока
                                return invertedIndexesForThread;
                            }
        );

        //Определить ID первого документа для следующего потока
        beginDocID = endDocID + 1;
    }

    try
    {
        /**
         * Cлияние инвертированных баз в одном потоке
         */

        /*
        //Ожидать завершения потоков
        for (auto &future: futures)
        {
            //InvertedIndex::invertedIndexesForThread = future.get();

            for (auto &elem: future.get())
            {
                //Найти слово в базе инвертированных индексов
                auto positionWord{invertedIndexes.find(elem.first)};

                //Слово в базе инвертированных индексов не существует
                if (positionWord == invertedIndexes.end())
                {
                    //Добавить слово c контейнером структур инвертированного индекса в базу инвертированных индексов
                    invertedIndexes.insert({std::move(elem.first), std::move(elem.second)});
                } else
                    //Слово в базе инвертированных индексов существует
                {
                    for (auto &entry: elem.second)
                    {
                        //Добавить структуру инвертированного индекса для нового ID документа по слову
                        invertedIndexes[elem.first].push_back(entry);
                    }
                }
            }
        }
    }//Cлияние инвертированных баз в одном потоке*/


        /**
         * Cлияние инвертированных баз в разных потоках
         */

        //Слить базы инвертированного индекса подготовленные в разных потоках
        mergeInvertedIndexBases(futures);

        //Получить результат в базу инвертированного индекса
        invertedIndexes = std::move(futures[0]).get();
    }//Cлияние инвертированных баз в разных потоках*/

    //Обработать все исключения, выброшенные в потоках
    catch (const std::exception& e)
    {
        //Регенерировать исключение выше. Будет обработано в главной функции
        throw;
    }
    //Инвертированная индексация документов в отдельных потоках*/


    /**
     * Инвертированная индексация документов в одном потоке
     */

    /*
    for (std::size_t docID{}; docID < documents.size(); ++docID)
    {

        defineWordOrReadDocumentAtBeginning(docID, documents[docID], invertedIndexes);
    }//Инвертированная индексация документов в одном потоке*/
}
