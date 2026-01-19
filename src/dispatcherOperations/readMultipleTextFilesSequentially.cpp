//
// Created by AKazmirchuk on 26.12.2025.
//



#include "dispatcherOperations.h"



std::pair<std::string, ErrorCode> DispatcherOperations::readMultipleTextFilesSequentially(
        const std::string& filePath,
        const std::size_t filesNumber,
        const std::size_t maximumAllowableErrorsNumber,
        const std::size_t packageID,
        const std::string& messageOneFile, const std::string& messageMultipleFiles,
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

    //Результат чтения текстового файла
    std::pair<std::string, ErrorCode> tmp;

    try
    {
        //Прочитать текстовый файл TODO возможно, надо читать не файл целеком, а слово в файле. Надо сделать замер
        tmp = DispatcherOperations::readTextFile(filePath, messageOneFile, errorLevelOneFile, BOOST_CURRENT_LOCATION);

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

            //Снять защиту на поиск и добавление ID пакета в контейнере соответствия
        }

        //Если была ошибка
        if (tmp.second != ErrorCode::no_error)
        {
            //Увеличить количество ошибок
            ++currentErrorsNumber[getFunctionName(callingFunction)][packageID].second;
        }
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        //Исключение "обработано". В первую очередь - для каждого файла с уровнем логирования fatal.
        //Установить признак выброса исключения при чтении каждого файла
        isFatalForOneFile = true;
    }

    //Увеличить количество прочитанных документов
    ++currentErrorsNumber[getFunctionName(callingFunction)][packageID].first;
    std::cout << '\n' << "current errorNumber: " << currentErrorsNumber[getFunctionName(callingFunction)][packageID].second;
    std::cout << '\n' << "current fileNumber: " << currentErrorsNumber[getFunctionName(callingFunction)][packageID].first << '\n';
    //Если все документы прочитаны
    if (currentErrorsNumber[getFunctionName(callingFunction)][packageID].first == filesNumber || isFatalForOneFile)
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
std::cout << '\n' << "errorNumber: " << errorNumber << ", " << "filesNumber: " << filesNumber << ", " << "errorLevelMultipleFiles: " << getStringFromErrorLevel(errorLevelMultipleFiles) << '\n';
        //Определить код ошибки и уровень логирования для всех файлов
        std::pair<ErrorCode, ErrorLevel> ErrorCodeAndLevel{determineErrorCodeAndErrorLevelForMultipleFiles(filesNumber, isFatalForOneFile, errorNumber, maximumAllowableErrorsNumber, errorLevelOneFile, errorLevelMultipleFiles, callingFunction)};

        //Логировать событие по коду ошибки и уровню логирования
        determineValidity("", ErrorCodeAndLevel.first, ErrorCodeAndLevel.second, messageMultipleFiles, callingFunction);
    }

    return tmp;
}