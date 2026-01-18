//
// Created by AKazmirchuk on 26.12.2025.
//



#include "dispatcherOperations.h"



std::pair<std::string, ErrorCode> DispatcherOperations::readMultipleTextFilesSequentially(
        const std::string& filePath,
        const std::size_t filesNumber,
        const std::size_t maximumAllowableErrorsNumber,
        const std::size_t packageID,
        const std::string& message,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const boost::source_location &callingFunction)
{
    /**
     * Контейнер соответствия имени вызывающей функции и, ID пакета (для отделения разных наборов файлов в потоках) и текущим количествам файлов и ошибок.
     * Используется в функции readMultipleTextFilesSequentially
     */
    /* std::map<std::string, //Имя функции, вида "DispatcherOperations::readMultipleTextFilesSequentially"
                          std::map<
                                   std::size_t, //ID пакета (для отделения разных наборов файлов в потоках)
                                   std::pair<
                                             std::atomic<std::size_t>, std::atomic<std::size_t> //Текущее количество файлов и ошибок в пакете
                                            >
                                  >
                         > currentErrorsNumber*/

    //Признак выброса исключения при чтении каждого файла
    bool isFatalForOneFile{};

    //Прочитать текстовый файл TODO возможно, надо читать не файл целеком, а слово в файле. Надо сделать замер
    std::pair<std::string, ErrorCode> tmp{DispatcherOperations::readTextFile(filePath, message, errorLevelOneFile, BOOST_CURRENT_LOCATION)};

    {
        //Установить защиту на поиск и добавление ID пакета в контейнер соответствия
        std::lock_guard<std::mutex> lgFindAddPackageID(DispatcherOperations::mutexFindAddPackageID);

        //Найти ID пакета в контейнере соответствия
        auto positionOfPackageID{currentErrorsNumber[getFunctionName(callingFunction)].find(packageID)};
        //Для тестов
        /*for (auto& elem : currentErrorsNumber)
        {
            std::cout << "1: " << elem.first << " ";
            for (auto& elem2 : elem.second)
            {
                std::cout << "2: " << elem2.first << " " << elem2.second.first << " " << elem2.second.second;
            }
            std::cout << " find" << '\n';
        }//Для тестов*/

        //ID пакета в контейнере соответствия не существует
        if (positionOfPackageID == currentErrorsNumber[getFunctionName(callingFunction)].end())
        {
            //Для тестов
            /*for (auto& elem : currentErrorsNumber)
            {
                std::cout << "1: " << elem.first << " ";
                for (auto& elem2 : elem.second)
                {
                    std::cout << "2: " << elem2.first << " " << elem2.second.first << " " << elem2.second.second;
                }
                std::cout << " before init" << '\n';
            }//Для тестов*/

            //Инициализировать блокировку объекта std::atomic<std::size_t> текущего количества файлов в пакете
            std::atomic_init(&currentErrorsNumber[getFunctionName(callingFunction)][packageID].first, 0);
            //Инициализировать блокировку объекта std::atomic<std::size_t> текущего количества ошибок в пакете
            std::atomic_init(&currentErrorsNumber[getFunctionName(callingFunction)][packageID].second, 0);
            //Для тестов
            /*for (auto& elem : currentErrorsNumber)
            {
                std::cout << "1: " << elem.first << " ";
                for (auto& elem2 : elem.second)
                {
                    std::cout << "2: " << elem2.first << " " << elem2.second.first << " " << elem2.second.second;
                }
                std::cout << " after init" << '\n';
            }//Для тестов*/
        }

        //Снять защиту на поиск и добавление ID пакета в контейнер соответствия
    }

    //Если была ошибка
    if (tmp.second != ErrorCode::no_error)
    {
        //Увеличить количество ошибок
        ++currentErrorsNumber[getFunctionName(callingFunction)][packageID].second;
    }

    //Увеличить количество прочитанных документов
    ++currentErrorsNumber[getFunctionName(callingFunction)][packageID].first;

    //Если все документы прочитаны
    if (currentErrorsNumber[getFunctionName(callingFunction)][packageID].first == filesNumber)
    {
        //Определить количество ошибок
        std::size_t errorNumber{currentErrorsNumber[getFunctionName(callingFunction)][packageID].second};

        //Удалить записи этого пакета для этой функции
        currentErrorsNumber[getFunctionName(callingFunction)].erase(packageID);
        //Для тестов
        /*for (auto& elem : currentErrorsNumber)
        {
            std::cout << "1: " << elem.first << " ";
            for (auto& elem2 : elem.second)
            {
                std::cout << "2: " << elem2.first << " " << elem2.second.first << " " << elem2.second.second;
            }
            std::cout << " after delete ID of package" << '\n';
        }//Для тестов*/
        //Если записей пакетов для этой функции нет
        if (currentErrorsNumber[getFunctionName(callingFunction)].empty())
        {
            //Удалить запись этой функции
            currentErrorsNumber.erase(getFunctionName(callingFunction));
        }
        //Для тестов
        /*for (auto& elem : currentErrorsNumber)
        {
            std::cout << "1: " << elem.first << " ";
            for (auto& elem2 : elem.second)
            {
                std::cout << "2: " << elem2.first << " " << elem2.second.first << " " << elem2.second.second;
            }
            std::cout << " after delete name of function" << '\n';
        }//Для тестов*/

        //Определить код ошибки и уровень логирования для всех файлов
        std::pair<ErrorCode, ErrorLevel> ErrorCodeAndLevel{determineErrorCodeAndErrorLevelForMultipleFiles(filesNumber, isFatalForOneFile, errorNumber, maximumAllowableErrorsNumber, errorLevelOneFile, errorLevelMultipleFiles, callingFunction)};

        //Логировать событие по коду ошибки и уровню логирования
        determineValidity("", ErrorCodeAndLevel.first, ErrorCodeAndLevel.second, message, callingFunction);
    }

    return tmp;
}