//
// Created by Alexander on 13.06.2025.
//



#include "dispatcherDetermineValidity.h"



ErrorCode DispatcherDetermineValidity::writeJSONFile(const std::string& filePath, const JSON& objectJSON, const int formatByWidth,
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

std::pair<JSON, ErrorCode> DispatcherDetermineValidity::readJSONFile(const std::string& filePath, ErrorLevel errorLevel,
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

std::pair<std::string, ErrorCode> DispatcherDetermineValidity::readTextFile(const std::string& filePath, ErrorLevel errorLevel,
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

ErrorCode DispatcherDetermineValidity::checkJSONStructureMatch(const std::string& filePath, const JSON& objectJSON, const JSON& objectJSONTemplate,
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

ErrorCode DispatcherDetermineValidity::checkFilePathsArray(JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
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

ErrorCode DispatcherDetermineValidity::checkRequestsArray(const JSON& objectJSON, ErrorLevel errorLevel, const std::string& message,
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

std::pair<std::vector<std::string>, ErrorCode> DispatcherDetermineValidity::readMultipleTextFiles(const std::vector<std::string> &filePaths, ErrorLevel errorLevel, const std::string& message,
                                                                                                  const boost::source_location &callingFunction)
{
    //Документы
    std::vector<std::string> documents;

    //Контейнер результатов потоков
    std::list<std::future<std::pair<std::string, ErrorCode>>> futures;

    //Для каждого документа
    for (std::size_t docID{}; docID < filePaths.size(); ++docID)
    {
        //Запустить чтение из файла
        futures.push_back(std::async(DispatcherDetermineValidity::readTextFile, std::cref(filePaths[docID]), ErrorLevel::error, "", BOOST_CURRENT_LOCATION));
    }
    //Количество непрочитанных документов
    std::size_t errorNumber{};

    try
    {
        //Ожидать завершение потоков
        for (auto &future: futures)
        {
            //Получить результат работы потока
            std::pair<std::string, ErrorCode> tmp{future.get()};

            //Добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
            documents.push_back(tmp.first);
            //Если при чтении произошла ошибка
            if (tmp.second != ErrorCode::no_error)
            {
                //Увеличить количество непрочитанных документов
                ++errorNumber;
            }
        }
    }
    catch (const std::exception& e)
    {
        //Регенерировать исключение выше. Будет обработано в главной функции
        throw;
    }

    //Определить код ошибки
    ErrorCode errorCode{ErrorCode::no_error};
    //Если все документы не прочитаны
    if (errorNumber == filePaths.size())
    {
        //Установить соответствующий код ошибки
        errorCode = ErrorCode::error_all_files_not_read;
    }
    //Логировать событие по коду ошибки и уровню логирования
    determineValidity("", errorCode, errorLevel, message, callingFunction);

    //Вернуть пару контейнера текстов и кода ошибки
    return {documents, errorCode};
}
