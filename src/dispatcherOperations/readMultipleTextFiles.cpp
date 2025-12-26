//
// Created by AKazmirchuk on 26.12.2025.
//



#include "DispatcherOperations.h"



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
        (errorLevelMultipleFiles == ErrorLevel::fatal || getErrorLevel(callingFunction) == ErrorLevel::fatal))
    {
        //Если используется уровень логирования напрямую - назначить уровень логирования для всех файлов как для одного
        if (errorLevelOneFile != ErrorLevel::no_level) errorLevelMultipleFiles = errorLevelOneFile;
            //В противном случае - понизить уровень логирования
        else errorLevelMultipleFiles = ErrorLevel::error;
    }

    return {error, errorLevelMultipleFiles};
}

std::pair<std::string, ErrorCode> DispatcherOperations::readTextFileFromMultipleFiles(
        const std::string& filePath,
        const std::string& message,
        ErrorLevel errorLevel,
        const boost::source_location &callingFunction)
{
    return DispatcherOperations::readTextFile(filePath, message, errorLevel, BOOST_CURRENT_LOCATION);
}

std::pair<std::vector<std::string>, std::vector<ErrorCode>> DispatcherOperations::readMultipleTextFilesImpl(
        const std::vector<std::string>& filePaths,
        const unsigned int desiredNumberOfThreads,
        const std::string& message,
        ErrorLevel errorLevel,
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
                        //TODO На горит. Попробовать обработать заранее допустимое количество ошибок чтения файла и выйти из двойного цикла
                        std::pair<std::string, ErrorCode> tmp{DispatcherOperations::readTextFileFromMultipleFiles(filePaths[currentDocID], message, errorLevel, callingFunction)};
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



    //------------------------------

    /*
     * Чтение документов в одном потоке
     */

    //Контейнер прочитанных документов с приведённым типом ошибок
/*    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents(filePaths.size(), filePaths.size());

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {

        std::pair<std::basic_string<char>, ErrorCode> tmp{DispatcherOperations::readTextFileFromMultipleFiles(filePaths[docID], message, errorLevel, callingFunction)};

        //Добавить документ в контейнер прочитанных документов
        documents.first[docID] = tmp.first;

        //Добавить код ошибки
        documents.second[docID] = tmp.second;
    }//Чтение документов в одном потоке*/



    //Вернуть пару контейнера текстов и кода ошибки
    return documents;
}

ResultOfReadMultipleTextFiles DispatcherOperations::readMultipleTextFiles(
        const std::vector<std::string> &filePaths,
        const unsigned int desiredNumberOfThreads,
        const std::size_t maximumAllowableErrorsNumber,
        const std::string& message,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const boost::source_location &callingFunction)
{
    //Timer test
    //Timer t;

    //Контейнер прочитанных документов с приведённым типом ошибок
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents{readMultipleTextFilesImpl(filePaths, desiredNumberOfThreads, message, errorLevelOneFile, callingFunction)};

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
    (errorLevelMultipleFiles == ErrorLevel::fatal || getErrorLevel(callingFunction) == ErrorLevel::fatal))
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