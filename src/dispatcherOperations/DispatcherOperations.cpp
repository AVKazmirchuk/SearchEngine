//
// Created by Alexander on 13.06.2025.
//



#include "DispatcherOperations.h"
#include "timer.h"


ErrorCode DispatcherOperations::writeJSONFile(
        const std::string& filePath,
        const JSON& objectJSON,
        const int formatByWidth,
        const std::string& message,
        ErrorLevel errorLevel,
        const boost::source_location &callingFunction)
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

std::pair<JSON, ErrorCode> DispatcherOperations::readJSONFile(
        const std::string& filePath,
        const std::string& message,
        ErrorLevel errorLevel,
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

ErrorCode DispatcherOperations::checkJSONStructureMatch(
        const std::string& filePath,
        const JSON& objectJSON, const JSON& objectJSONTemplate,
        const std::string& message,
        ErrorLevel errorLevel,
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

ErrorCode DispatcherOperations::checkFilePathsArray(
        const JSON& objectJSON,
        const std::string& message,
        ErrorLevel errorLevel,
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

ErrorCode DispatcherOperations::checkRequestsArray(
        const JSON& objectJSON,
        const std::string& message,
        ErrorLevel errorLevel,
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

std::pair<std::string, ErrorCode> DispatcherOperations::readTextFile(
        const std::string& filePath,
        const std::string& message,
        ErrorLevel errorLevel,
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



//------------------------------

/**
 * Для тестирования передачи контейнера по ссылке
 */

void DispatcherOperations::readTextFileRef(
        const std::string& filePath, std::string &document,
        ErrorCode &errorCode,
        const std::string& message,
        ErrorLevel errorLevel,
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
}

void DispatcherOperations::readMultipleTextFilesImplRef(
        const std::vector<std::string>& filePaths,
        std::pair<std::vector<std::string>, std::vector<ErrorCode>> &documents,
        const std::string &message,
        ErrorLevel errorLevel,
        const boost::source_location &callingFunction)
{
    //Установить размеры контейнеров документов и ошибок
    documents.first.resize(filePaths.size());
    documents.second.resize(filePaths.size());

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Прочитать текстовый файл
        DispatcherOperations::readTextFileRef(filePaths[docID], documents.first[docID], errorLevel, documents.second[docID], message, callingFunction);

    }
}

void DispatcherOperations::readMultipleTextFilesRef(
        const std::vector<std::string>& filePaths,
        ResultOfReadMultipleTextFiles &documents,
        std::size_t maximumAllowableErrorsNumber,
        const std::string& message,
        ErrorLevel errorLevelOneFile, ErrorLevel errorLevelMultipleFiles,
        const boost::source_location &callingFunction)
{
    //Контейнер прочитанных документов с приведённым типом ошибок
    readMultipleTextFilesImplRef(filePaths, documents.documentsAndErrors, message, errorLevelOneFile, callingFunction);

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
        (errorLevelMultipleFiles == ErrorLevel::fatal || getErrorLevel(callingFunction) == ErrorLevel::fatal))
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
}//Для тестирования передачи контейнера по ссылке*/