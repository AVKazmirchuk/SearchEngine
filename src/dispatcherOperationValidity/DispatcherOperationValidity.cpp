//
// Created by Alexander on 13.06.2025.
//



#include "DispatcherOperationValidity.h"
#include "timer.h"


ErrorCode DispatcherOperationValidity::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth,
                                                     ErrorLevel errorLevel, const std::string& message, const boost::source_location &callingFunction)
{
    //Записать JSON-файл
    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::writeJSONFile(filePath, objectJSON, formatByWidth)};
    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    //Вернуть код ошибки
    return errorCode;
}

std::pair<JSON, ErrorCode> DispatcherOperationValidity::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                     const std::string& message,
                                                                     const boost::source_location &callingFunction)
{
    //Прочитать JSON-файл
    std::pair<JSON, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readJSONFile(filePath)};
    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    std::pair<JSON, ErrorCode> tmp{std::move(tmpOriginal.first), convertErrorCodeFrom(tmpOriginal.second)};
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    //Вернуть пару JSON-объекта и кода ошибки
    return tmp;

}

ErrorCode DispatcherOperationValidity::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
                                                               ErrorLevel errorLevel, const std::string& message,
                                                               const boost::source_location &callingFunction)
{
    //Проверить JSON-структуру на соответствие шаблону
    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkJSONStructureMatch(objectJSON, objectJSONTemplate)};
    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);

    //Вернуть код ошибки
    return errorCode;
}

ErrorCode DispatcherOperationValidity::checkFilePathsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                           const boost::source_location &callingFunction)
{
    //Проверить массив JSON-объекта на пустоту
    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkArray(objectJSON)};
    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};
    //Если код ошибки равен общему
    if (errorCode == ErrorCode::error_array_empty)
    {
        //Вернуть точный код ошибки
        errorCode = ErrorCode::error_file_paths_array_empty;
    }

    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", errorCode, errorLevel, message, callingFunction);

    //Вернуть код ошибки
    return errorCode;
}

ErrorCode DispatcherOperationValidity::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
                                                          const boost::source_location &callingFunction)
{
    //Проверить массив JSON-объекта на пустоту
    kav::ErrorCode errorCodeOriginal{kav::OperationFileAndJSON::checkArray(objectJSON)};
    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    ErrorCode errorCode{convertErrorCodeFrom(errorCodeOriginal)};
    //Если код ошибки равен общему
    if (errorCode == ErrorCode::error_array_empty)
    {
        //Вернуть точный код ошибки
        errorCode = ErrorCode::error_requests_array_empty;
    }
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", errorCode, errorLevel, message, callingFunction);

    //Вернуть код ошибки
    return errorCode;
}

std::pair<std::string, ErrorCode> DispatcherOperationValidity::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
                                                                            const std::string& message,
                                                                            const boost::source_location &callingFunction)
{
    //Прочитать текстовый файл
    std::pair<std::string, kav::ErrorCode> tmpOriginal{kav::OperationFileAndJSON::readTextFile(filePath)};
    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    std::pair<std::string, ErrorCode> tmp{std::move(tmpOriginal.first), convertErrorCodeFrom(tmpOriginal.second)};
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    //Вернуть пару текста и кода ошибки
    return tmp;
}

std::pair<std::vector<std::string>, std::vector<ErrorCode>> DispatcherOperationValidity::readMultipleTextFiles(
        const std::vector<std::string> &filePaths, const unsigned int desiredNumberOfThreads, ErrorLevel errorLevel,
        const std::string& message, const boost::source_location &callingFunction)
{
    //Timer test
    Timer t;

    /*
     * Чтение документов в нескольких потоках
     */

    /*
    //Контейнер прочитанных документов
    std::pair<std::vector<std::string>, ErrorCode> documents;

    //Если количество документов меньше либо равно желаемого количества потоков - использовать количество потоков равным количеству документов.
    //В противном случае - использовать желаемое количество потоков.
    int numberOfThreads = filePaths.size() <= desiredNumberOfThreads ? filePaths.size() : desiredNumberOfThreads;

    //Определить разницу количества документов между потоками
    std::size_t difference{filePaths.size() / numberOfThreads};

    if (filePaths.size() % numberOfThreads)
    {
        ++numberOfThreads;
    }

    //Контейнер результатов потоков
    std::list<std::future<std::vector<std::pair<std::string, ErrorCode>>>> futures(numberOfThreads);


    std::size_t beginDocID{};

    //Для каждого будущего потока
    for (auto &future : futures)
    {
        std::size_t endDocID{beginDocID + difference - 1};

        if (endDocID >= filePaths.size()) endDocID = filePaths.size() - 1;

        //std::cout << "beginDocID: " << beginDocID << ", endDocID: " << endDocID << '\n';

        //Запустить чтение файлов в своём диапазоне
        future = std::async(
                [beginDocID, endDocID, &filePaths, &errorLevel, &message, &callingFunction]()
            {
                //Контейнер пар прочитанных документов и кодов ошибок
                std::vector<std::pair<std::string, ErrorCode>> documents;

                //Количество непрочитанных документов
                std::size_t errorNumber{};

                //Для каждого документа
                for (std::size_t currentDocID{beginDocID}; currentDocID <= endDocID; ++currentDocID)
                    {
                        //Запустить чтение из файла и добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
                        documents.push_back(DispatcherOperationValidity::readTextFile(filePaths[currentDocID]));
                    }

                //Вернуть контейнер пар прочитанных документов и кодов ошибок
                return documents;
            }
        );

        beginDocID = endDocID + 1;
    }

    //Количество непрочитанных документов
    std::size_t errorNumber{};

    try
    {
        //Ожидать завершение потоков
        for (auto &future : futures)
        {
            //Получить результат работы потока
            std::vector<std::pair<std::string, ErrorCode>> tmp{future.get()};

            //Для каждого документа
            for (auto &document : tmp)
            {
                //Добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
                documents.first.push_back(std::move(document.first));
                //Если при чтении произошла ошибка
                if (document.second != ErrorCode::no_error)
                {
                    //Увеличить количество непрочитанных документов
                    ++errorNumber;
                }
               }
        }
    }
    catch (const std::exception& e)
    {
        //Регенерировать исключение выше. Будет обработано в главной функции
        throw;
    }//Чтение документов в нескольких потоках*/

    /*
     * Чтение документов в одном потоке
     */


    //Контейнер прочитанных документов с приведённым типом ошибок
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents;

    //Прочитать текстовые файлы
    std::pair<std::vector<std::string>, std::vector<kav::ErrorCode>> documentsOriginal{kav::OperationFileAndJSON::readMultipleTextFiles(filePaths, desiredNumberOfThreads)};

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Добавить документ в контейнер прочитанных документов
        documents.first.push_back(std::move(documentsOriginal.first[docID]));
        //documents.first = std::move(documentsOriginal.first);
        //Преобразовать код ошибки из типа внешней функции во внутренний тип
        documents.second.push_back(convertErrorCodeFrom(documentsOriginal.second[docID]));
    }//Чтение документов в одном потоке*/

    //Количество непрочитанных документов
    std::size_t errorNumber{};

    //Для каждого кода ошибки документов
    for (auto error : documents.second)
    {
        //Если при чтении произошла ошибка
        if (error != ErrorCode::no_error)
        {
            //Увеличить количество непрочитанных документов
            ++errorNumber;
        }
    }

    //Определить код ошибки для всех документов
    ErrorCode error = ErrorCode::no_error;

    //Если все документы не прочитаны
    if (errorNumber == filePaths.size())
    {
        //Установить соответствующий код ошибки
        error = ErrorCode::error_all_files_not_read;
    }
    else if (errorNumber > 0)
    {
        error = ErrorCode::error_any_files_not_read;
    }

    //Для тестирования производительности
    //std::cout << '\n' << "numberOfThreads: " << numberOfThreads << '\n';
    std::cout << '\n' << sizeof(documents) << '\n';
    std::cout << '\n' << t.elapsed() << '\n';

    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", documents.second, errorLevel, message, callingFunction);

    //Вернуть пару контейнера текстов и кода ошибки
    return documents;
}

void DispatcherOperationValidity::readTextFileRef(const std::string& filePath, std::pair<std::string, ErrorCode> &tmp, ErrorLevel errorLevel,
                                                  const std::string& message,
                                                  const boost::source_location &callingFunction)
{
    //Прочитать текстовый файл
    std::pair<std::string, kav::ErrorCode> tmpOriginal;
    kav::OperationFileAndJSON::readTextFileRef(filePath, tmpOriginal);
    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    tmp = {std::move(tmpOriginal.first), convertErrorCodeFrom(tmpOriginal.second)};
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity(filePath, tmp.second, errorLevel, message, callingFunction);

    //Вернуть пару текста и кода ошибки
    //return tmp;
}

void DispatcherOperationValidity::readMultipleTextFilesRef(const std::vector<std::string>& filePaths, std::pair<std::vector<std::string>, ErrorCode> &documents, const unsigned int desiredNumberOfThreads, ErrorLevel errorLevel,
                              const std::string &message,
                              const boost::source_location &callingFunction)
{
    //Timer test
    Timer t;

    /*
     * Чтение документов в одном потоке
     */

    //Контейнер прочитанных документов
    //std::vector<std::string> documents;

    //Количество непрочитанных документов
    std::size_t errorNumber{};

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        std::pair<std::string, ErrorCode> tmp;
        DispatcherOperationValidity::readTextFileRef(filePaths[docID], tmp, ErrorLevel::error, "", BOOST_CURRENT_LOCATION);
        //Добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
        documents.first.push_back(std::move(tmp.first));
        //Если при чтении произошла ошибка
        if (tmp.second != ErrorCode::no_error)
        {
            //Увеличить количество непрочитанных документов
            ++errorNumber;
        }
    }//Чтение документов в одном потоке

    //Определить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};
    //Если все документы не прочитаны
    if (errorNumber == filePaths.size())
    {
        //Установить соответствующий код ошибки
        errorCode = ErrorCode::error_all_files_not_read;
    }

    //Для тестирования производительности
    //std::cout << '\n' << "numberOfThreads: " << numberOfThreads << '\n';
    std::cout << '\n' << sizeof(documents) << '\n';
    std::cout << '\n' << t.elapsed() << '\n';

    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", errorCode, errorLevel, message, callingFunction);

    documents.second = errorCode;
    //Вернуть пару контейнера текстов и кода ошибки
    //return {documents, errorCode};
}