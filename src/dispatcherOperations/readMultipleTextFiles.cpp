//
// Created by AKazmirchuk on 26.12.2025.
//



#include "dispatcherOperations.h"



std::pair<ErrorCode, ErrorLevel> DispatcherOperations::determineErrorCodeAndErrorLevelForMultipleFiles(
        const std::size_t filesNumber,
        bool isFatalForOneFile,
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

std::cout << getStringFromErrorLevel(errorLevelOneFile) << ' ' << getStringFromErrorLevel(errorLevelMultipleFiles) << ' ' << errorNumber << ' ' << maximumAllowableErrorsNumber;





    //Если количество ошибок не превышает максимально допустимого и, уровень логирования для всех файлов установлен как фатальный или
    //функция, из которой вызывается чтение документов, помечена как фатальная
    if (errorNumber <= maximumAllowableErrorsNumber && errorLevelMultipleFiles == ErrorLevel::fatal)
    {
        std::cout << "qqq";

        if (errorLevelOneFile != ErrorLevel::fatal) errorLevelMultipleFiles = ErrorLevel::error;
        //Если используется уровень логирования напрямую - назначить уровень логирования для всех файлов как для одного
        /*if (errorLevelOneFile != ErrorLevel::no_level) errorLevelMultipleFiles = errorLevelOneFile;
            //В противном случае - понизить уровень логирования
        else if (errorLevelOneFile != ErrorLevel::fatal && errorLevelMultipleFiles == ErrorLevel::fatal) errorLevelMultipleFiles = ErrorLevel::error;//*/
    }
std::cout << getStringFromErrorLevel(errorLevelMultipleFiles);
    return {error, errorLevelMultipleFiles};
}

std::pair<std::string, ErrorCode> DispatcherOperations::readTextFileFromMultipleFiles(
        const std::string& filePath,
        const std::string& message,
        ErrorLevel errorLevel,
        const boost::source_location &callingFunction)
{
    std::cout << "errorLevel: " << getStringFromErrorLevel(errorLevel);
    return DispatcherOperations::readTextFile(filePath, message, errorLevel, BOOST_CURRENT_LOCATION);
}

std::pair<std::vector<std::string>, std::vector<ErrorCode>> DispatcherOperations::readMultipleTextFilesImpl(
        const std::vector<std::string>& filePaths,
        const unsigned int desiredNumberOfThreads,
        const std::string& message,
        ErrorLevel errorLevel,
        const boost::source_location &callingFunction)
{
    //Контейнер прочитанных документов
    std::pair<std::vector<std::string>, std::vector<ErrorCode>> documents(filePaths.size(), filePaths.size());

    //Прочитать документы независимо от количества потоков
    auto readTextFile = [&documents, &filePaths, &message, &errorLevel, &callingFunction](std::size_t beginDocID, std::size_t endDocID)
    {
        //Для каждого документа
        for (std::size_t currentDocID{beginDocID}; currentDocID < endDocID; ++currentDocID)
        {
            //Запустить чтение из файла и добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
            //TODO Не горит. Попробовать обработать заранее допустимое количество ошибок чтения файла и выйти из двойного цикла
            std::pair<std::string, ErrorCode> tmp{DispatcherOperations::readTextFileFromMultipleFiles(filePaths[currentDocID], message, errorLevel, callingFunction)};
            //Скопировать (переместить) результаты в контейнер прочитанных документов
            documents.first[currentDocID] = std::move(tmp.first);
            documents.second[currentDocID] = tmp.second;

        }
    };

    //Определить количество потоков
    std::size_t difference{countNumberOfThreads(filePaths, desiredNumberOfThreads)};

    //Если дополнительных потоков нет
    if (numberOfThreads == 0)
    {
        //Прочитать документы в текущем потоке
        readTextFile(0, filePaths.size());
    }
    else
    //Есть дополнительные потоки
    {
         //Контейнер результатов потоков
        std::list<std::future<void>> futures(numberOfThreads);

        //ID первого документа для каждого потока
        std::size_t beginDocID{};

        //Для каждого будущего потока
        for (auto &future: futures)
        {
            //ID последнего документа для каждого потока
            std::size_t endDocID{beginDocID + difference - 1};

            //Если ID последнего документа для потока превышает ID документа всех документов
            if (endDocID >= filePaths.size()) endDocID = filePaths.size() - 1;

            //Запустить чтение файлов в своём диапазоне
            future = std::async(
                    [&readTextFile, beginDocID, endDocID]() mutable
                    {
                        //Прочитать документы в дополнительном потоке
                        readTextFile(beginDocID, ++endDocID);
                    }
            );

            //Определить ID первого документа для следующего потока
            beginDocID = endDocID + 1;
        }

        try
        {
            //Ожидать завершение потоков
            for (auto &future: futures)
            {
                //Получить результат работы потока
                future.get();
            }
        }
        catch (const DispatcherOperations::OperationException &exception)
        {
            std::cout << "from readMultipleTextFilesImpl, throw";
            //Регенерировать исключение выше. Будет обработано в главной функции
            throw;
        }

    }

    //Вернуть пару контейнера текстов и кода ошибки
    return documents;
}

ResultOfReadMultipleTextFiles DispatcherOperations::readMultipleTextFiles(
        const std::vector<std::string> &filePaths,
        const unsigned int desiredNumberOfThreads,
        const std::size_t maximumAllowableErrorsNumber,
        const std::string& messageOneFile, const std::string& messageMultipleFiles,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const boost::source_location &callingFunction)
{
    //Определить уровни логирования. Используется ли соответствие имени вызывающей функции и уровня логирования
    errorLevelMultipleFiles = determineErrorLevel(errorLevelMultipleFiles, callingFunction);

    //Контейнер прочитанных документов с приведённым типом ошибок
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> documents(filePaths.size(), filePaths.size());

    //Количество непрочитанных документов
    std::size_t errorNumber{};

    //Признак выброса исключения при чтении каждого файла
    bool isFatalForOneFile{};

    try
    {
        //Прочитать файлы
        documents = std::move(readMultipleTextFilesImpl(filePaths, desiredNumberOfThreads, messageOneFile, errorLevelOneFile, callingFunction));

        //Подсчитать количество непрочитанных документов
        errorNumber = countErrorsNumber(documents.second);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        //Исключение "обработано". В первую очередь - для каждого файла с уровнем логирования fatal.
        //Установить признак выброса исключения при чтении каждого файла
        isFatalForOneFile = true;
    }

    //Определить уровни логирования. Используется ли соответствие имени вызывающей функции и уровня логирования
    errorLevelOneFile = determineErrorLevel(errorLevelOneFile, callingFunction);
    
    //Определить код ошибки и уровень логирования для всех файлов
    std::pair<ErrorCode, ErrorLevel> tmp{determineErrorCodeAndErrorLevelForMultipleFiles(filePaths.size(), isFatalForOneFile, errorNumber, maximumAllowableErrorsNumber, errorLevelOneFile, errorLevelMultipleFiles, callingFunction)};

    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", tmp.first, tmp.second, messageMultipleFiles, callingFunction);

    //Вернуть структуру результатов чтения текстовых файлов
    return ResultOfReadMultipleTextFiles{documents, errorNumber, tmp.first};
}