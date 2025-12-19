//
// Created by Alexander on 13.06.2025.
//



#include "DispatcherOperations.h"
#include "timer.h"


ErrorCode DispatcherOperations::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth,
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

std::pair<JSON, ErrorCode> DispatcherOperations::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
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

ErrorCode DispatcherOperations::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
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

ErrorCode DispatcherOperations::checkFilePathsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
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

ErrorCode DispatcherOperations::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
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

std::pair<std::string, ErrorCode> DispatcherOperations::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
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

std::pair<std::string, ErrorCode> DispatcherOperations::readTextFileFromMultipleFiles(const std::string& filePath, ErrorLevel errorLevel,
                                                                            const std::string& message,
                                                                            const boost::source_location &callingFunction)
{
    return DispatcherOperations::readTextFile(filePath, errorLevel, message, BOOST_CURRENT_LOCATION);
}

std::pair<std::vector<std::string>, std::vector<ErrorCode>> DispatcherOperations::readMultipleTextFilesImpl(
        const std::vector<std::string>& filePaths,
        const unsigned int desiredNumberOfThreads,
        ErrorLevel errorLevel,
        const std::string &message,
        const boost::source_location &callingFunction)
{

    /*
     * Чтение документов в нескольких потоках
     */

    //Контейнер прочитанных документов
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents(filePaths.size(), filePaths.size());

    //Определить количество потоков
    std::pair<std::size_t, const unsigned int> tmp{countNumberOfThreads(filePaths, desiredNumberOfThreads)};

    //Количество документов обрабатываемое одним потокам
    std::size_t difference{tmp.first};

    //Определить количество дополнительных потоков
    const unsigned int numberOfThreads = tmp.second;

    //Контейнер результатов потоков
    std::list<std::future<void>> futures(numberOfThreads);

    //ID первого документа для каждого потока
    std::size_t beginDocID{};

    //Для каждого будущего потока
    for (auto &future : futures)
    {
        //ID последнего документа для каждого потока
        std::size_t endDocID{beginDocID + difference - 1};

        //Если ID последнего документа для потока превышает ID документа всех документов
        if (endDocID >= filePaths.size()) endDocID = filePaths.size() - 1;

        //Запустить чтение файлов в своём диапазоне
        future = std::async(
                [beginDocID, endDocID, &documents, &filePaths, &errorLevel, &message, &callingFunction]()
            {
                //Для каждого документа
                for (std::size_t currentDocID{beginDocID}; currentDocID <= endDocID; ++currentDocID)
                    {
                        //Запустить чтение из файла и добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
                        //TODO Попробовать обработать заранее допустимое количество ошибок чтения файла и выйти из двойного цикла
                        std::pair<std::string, ErrorCode> tmp{DispatcherOperations::readTextFileFromMultipleFiles(filePaths[currentDocID], errorLevel, message, callingFunction)};
                        //Скопировать (переместить) результаты в контейнер прочитанных документов
                        documents.first[currentDocID] = std::move(tmp.first);
                        documents.second[currentDocID] = tmp.second;

                    }
            }
        );

        //Определить ID первого документа для следующего потока
        beginDocID = endDocID + 1;
    }

    try
    {
        //Ожидать завершение потоков
        for (auto &future : futures)
        {
            //Получить результат работы потока
            future.wait();
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

    /*
    //Контейнер прочитанных документов с приведённым типом ошибок
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents(filePaths.size(), filePaths.size());

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {

        std::pair<std::basic_string<char>, ErrorCode> tmp{DispatcherOperations::readTextFileFromMultipleFiles(filePaths[docID], errorLevel, message, callingFunction)};

        //Добавить документ в контейнер прочитанных документов
        documents.first[docID] = tmp.first;

        //Добавить код ошибки
        documents.second[docID] = tmp.second;
    }//Чтение документов в одном потоке*/



    //Для тестирования производительности
    //std::cout << '\n' << "numberOfThreads: " << numberOfThreads << '\n';

    //Вернуть пару контейнера текстов и кода ошибки
    return documents;
}

std::pair<ErrorCode, ErrorLevel> DispatcherOperations::determineErrorCodeAndErrorLevelForMultipleFiles(
        const std::size_t filesNumber,
        const std::size_t errorNumber, const std::size_t maximumAllowableErrorsNumber,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const boost::source_location &callingFunction)
{
    //Определить общий код ошибки (результат) при чтении всех документов
    ErrorCode error = ErrorCode::no_error;

    //Если все документы не прочитаны
    if (errorNumber == filesNumber)
    {
        //Установить соответствующий код ошибки
        error = ErrorCode::error_all_files_not_read;
    }
        //В противном случае, если есть какие-то ошибки
    else if (errorNumber > 0)
    {
        //Установить соответствующий код ошибки
        error = ErrorCode::error_any_files_not_read;
    }

    //Если количество ошибок не превышает максимально допустимого и, уровень логирования для всех файлов установлен как фатальный или
    //функция, из которой вызывается чтение документов, помечена как фатальная
    if (errorNumber <= maximumAllowableErrorsNumber &&
        (errorLevelMultipleFiles == ErrorLevel::fatal || getErrorLevel(callingFunction.to_string()) == ErrorLevel::fatal))
    {
        //Если используется уровень логирования напрямую - назначить уровень логирования для всех файлов как для одного
        if (errorLevelOneFile != ErrorLevel::no_level) errorLevelMultipleFiles = errorLevelOneFile;
            //В противном случае - понизить уровень логирования
        else errorLevelMultipleFiles = ErrorLevel::error;
    }

    return {error, errorLevelMultipleFiles};
}

ResultOfReadMultipleTextFiles DispatcherOperations::readMultipleTextFiles(
        const std::vector<std::string> &filePaths,
        const unsigned int desiredNumberOfThreads,
        const std::size_t maximumAllowableErrorsNumber,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const std::string& message,
        const boost::source_location &callingFunction)
{
    //Timer test
    //Timer t;

    //Контейнер прочитанных документов с приведённым типом ошибок
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents{readMultipleTextFilesImpl(filePaths, desiredNumberOfThreads, errorLevelOneFile, message, callingFunction)};

    //std::cout << '\n' << sizeof(documents) << '\n';
    //std::cout << '\n' << t.elapsed() << '\n';

    //Подсчитать количество непрочитанных документов
    std::size_t errorNumber{countErrorsNumber(documents.second)};

    /*//Определить общий код ошибки (результат) при чтении всех документов
    ErrorCode error = ErrorCode::no_error;

    //Если все документы не прочитаны
    if (errorNumber == filePaths.size())
    {
        //Установить соответствующий код ошибки
        error = ErrorCode::error_all_files_not_read;
    }
    //В противном случае, если есть какие-то ошибки
    else if (errorNumber > 0)
    {
        //Установить соответствующий код ошибки
        error = ErrorCode::error_any_files_not_read;
    }

    //Если количество ошибок не превышает максимально допустимого и, уровень логирования для всех файлов установлен как фатальный или
    //функция, из которой вызывается чтение документов, помечена как фатальная
    if (errorNumber <= maximumAllowableErrorsNumber &&
    (errorLevelMultipleFiles == ErrorLevel::fatal || getErrorLevel(callingFunction.to_string()) == ErrorLevel::fatal))
    {
        //Если используется уровень логирования напрямую - назначить уровень логирования для всех файлов как для одного
        if (errorLevelOneFile != ErrorLevel::no_level) errorLevelMultipleFiles = errorLevelOneFile;
        //В противном случае - понизить уровень логирования
        else errorLevelMultipleFiles = ErrorLevel::error;
    }*/

    //Определить код ошибки и уровень логирования для всех файлов
    std::pair<ErrorCode, ErrorLevel> tmp{determineErrorCodeAndErrorLevelForMultipleFiles(filePaths.size(), errorNumber, maximumAllowableErrorsNumber, errorLevelOneFile, errorLevelMultipleFiles, callingFunction)};

    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", tmp.first, tmp.second, message, callingFunction);

    //Вернуть структуру результатов чтения текстовых файлов
    return ResultOfReadMultipleTextFiles{documents, errorNumber, tmp.first};
}

std::pair<std::string, ErrorCode> DispatcherOperations::readMultipleTextFilesSequentially(
        const std::string& filePath,
        const std::size_t filesNumber,
        const std::size_t packageID,
        const std::size_t maximumAllowableErrorsNumber,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const std::string& message,
        const boost::source_location &callingFunction)
{

    //Прочитать текстовый файл
    std::pair<std::string, ErrorCode> tmp{DispatcherOperations::readTextFile(filePath, errorLevelOneFile, message, BOOST_CURRENT_LOCATION)};

    //Увеличить количество прочитанных документов
    ++currentErrorsNumber[getFunctionName(callingFunction)][packageID].first;

    //Если была ошибка
    if (tmp.second != ErrorCode::no_error)
    {
        //Увеличить количество ошибок
        ++currentErrorsNumber[getFunctionName(callingFunction)][packageID].second;
    }

    //Если все документы прочитаны
    if (currentErrorsNumber[getFunctionName(callingFunction)][packageID].first == filesNumber)
    {
        std::size_t errorNumber{currentErrorsNumber[getFunctionName(callingFunction)][packageID].second};

        //Удалить записи этого пакета для этой функции
        currentErrorsNumber[getFunctionName(callingFunction)].erase(packageID);

        //Если записей пакетов для этой функции нет
        if (currentErrorsNumber[getFunctionName(callingFunction)].empty())
        {
            //Удалить запись этой функции
            currentErrorsNumber.erase(getFunctionName(callingFunction));
        }

        //Определить код ошибки и уровень логирования для всех файлов
        std::pair<ErrorCode, ErrorLevel> ErrorCodeAndLevel{determineErrorCodeAndErrorLevelForMultipleFiles(filesNumber, errorNumber, maximumAllowableErrorsNumber, errorLevelOneFile, errorLevelMultipleFiles, callingFunction)};

        //Логировать событие по коду ошибки и уровню логирования
        determineValidity("", ErrorCodeAndLevel.first, ErrorCodeAndLevel.second, message, callingFunction);
    }

    return tmp;

    /*inline static std::map<std::string,
            std::map<
                    std::size_t,
                    std::pair<
                            std::atomic<std::size_t>, std::atomic<std::size_t>
                    >
            >
    > currentErrorsNumber{};*/
}

//Для тестирования передачи контейнера по ссылке
/*void DispatcherOperations::readTextFileRef(const std::string& filePath, std::string &document, ErrorCode &errorCode, ErrorLevel errorLevel,
                                                  const std::string& message,
                                                  const boost::source_location &callingFunction)
{
    //Объявить временную переменную для конвертации типа
    kav::ErrorCode tmpError;
    //Прочитать текстовый файл
    kav::OperationFileAndJSON::readTextFileRef(filePath, document, tmpError);

    //Преобразовать код ошибки из внешней функции во внутренний код ошибки
    errorCode = convertErrorCodeFrom(tmpError);
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity(filePath, errorCode, errorLevel, message, callingFunction);
}*/

//Для тестирования передачи контейнера по ссылке
/*void DispatcherOperations::readMultipleTextFilesImplRef(
        const std::vector<std::string>& filePaths,
        std::pair<std::vector<std::string>, std::vector<ErrorCode>> &documents,
        ErrorLevel errorLevel,
        const std::string &message,
        const boost::source_location &callingFunction)
{
    //Установить размеры контейнеров документов и ошибок
    documents.first.resize(filePaths.size());
    documents.second.resize(filePaths.size());

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Прочитать текстовый файл
        DispatcherOperations::readTextFileRef(filePaths[docID], documents.first[docID], documents.second[docID], errorLevel, message, callingFunction);

    }
}*/

//Для тестирования передачи контейнера по ссылке
/*void DispatcherOperations::readMultipleTextFilesRef(
        const std::vector<std::string>& filePaths,
        ResultOfReadMultipleTextFiles &documents,
        std::size_t maximumAllowableErrorsNumber,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const std::string& message,
        const boost::source_location &callingFunction)
{
    //Timer test
    //Timer t;

    //Контейнер прочитанных документов с приведённым типом ошибок
    readMultipleTextFilesImplRef(filePaths, documents.documentsAndErrors, errorLevelOneFile, message, callingFunction);

    //Подсчитать количество непрочитанных документов
    std::size_t errorNumber{countErrorsNumber(documents.documentsAndErrors.second)};

    //Определить общий код ошибки (результат) при чтении всех документов
    ErrorCode error = ErrorCode::no_error;

    //Если все документы не прочитаны
    if (errorNumber == filePaths.size())
    {
        //Установить соответствующий код ошибки
        error = ErrorCode::error_all_files_not_read;
    }
    //В противном случае, если есть какие-то ошибки
    else if (errorNumber > 0)
    {
        //Установить соответствующий код ошибки
        error = ErrorCode::error_any_files_not_read;
    }

    //Если количество ошибок не превышает максимально допустимого и, уровень логирования для всех файлов установлен как фатальный или
    //функция, из которой вызывается чтение документов, помечена как фатальная
    if (errorNumber <= maximumAllowableErrorsNumber &&
        (errorLevelMultipleFiles == ErrorLevel::fatal || getErrorLevel(callingFunction.to_string()) == ErrorLevel::fatal))
    {
        //Если используется уровень логирования напрямую - назначить уровень логирования для всех файлов как для одного
        if (errorLevelOneFile != ErrorLevel::no_level) errorLevelMultipleFiles = errorLevelOneFile;
            //В противном случае - понизить уровень логирования
        else errorLevelMultipleFiles = ErrorLevel::error;
    }

    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", error, errorLevelMultipleFiles, message, callingFunction);

    //Установить количество ошибок и общий код ошибки
    documents.errorNumber = errorNumber;
    documents.errorCode = error;
}*/