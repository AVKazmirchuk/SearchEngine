//
// Created by AKazmirchuk on 19.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции readMultipleTextFilesSequentially

/**
      * Прочитать несколько текстовых файлов последовательно для разных наборов потоков
      * @param filePath Ссылка на путь текстового файла
      * @param filesNumber Количество файлов
      * @param maximumAllowableErrorsNumber Максимально возможное количество ошибок
      * @param packageID ID пакета для разных потоков
      * @param messageOneFile Ссылка на сообщение для каждого файла
      * @param messageMultipleFiles Ссылка на сообщение для всех файлов
      * @param errorLevelOneFile Уровень логирования для одного фойла
      * @param errorLevelMultipleFiles Уровень логирования для всех файлов
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Пара текста и кода ошибки
      */
std::pair<std::string, ErrorCode> testReadMultipleTextFilesSequentially(
        const std::string& filePath,
        const std::size_t filesNumber,
        const std::size_t maximumAllowableErrorsNumber = 0,
        const std::size_t packageID = 0,
        const std::string& messageOneFile = "", const std::string& messageMultipleFiles = "",
        ErrorLevel errorLevelOneFile = ErrorLevel::no_level, ErrorLevel errorLevelMultipleFiles = ErrorLevel::no_level,
        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION)
{
    //Прочитать документы
    return DispatcherOperations::readMultipleTextFilesSequentially(filePath, filesNumber, maximumAllowableErrorsNumber, packageID,
                                                       messageOneFile, messageMultipleFiles, errorLevelOneFile, errorLevelMultipleFiles);
}

std::pair <std::vector<std::string>, std::vector<ErrorCode>> readFilePathsSequentially(const std::vector<std::string> &filePaths,
                                                const std::size_t filesNumber,
                                                const std::size_t maximumAllowableErrorsNumber,
                                                const std::size_t packageID,
                                                const std::string& messageOneFile, const std::string& messageMultipleFiles,
                                                ErrorLevel errorLevelOneFile = ErrorLevel::no_level, ErrorLevel errorLevelMultipleFiles = ErrorLevel::no_level)
{
    //Контейнер прочитанных документов с приведённым типом ошибок
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> documents(filePaths.size(), filePaths.size());

    //Для каждого документа
    for (std::size_t currentDocID{}; currentDocID < filePaths.size(); ++currentDocID)
    {
        //Запустить чтение из файла и добавить документ в любом случае (даже если он пустой), так как в будущем надо учитывать его ID
        std::pair<std::string, ErrorCode> tmp{testReadMultipleTextFilesSequentially(filePaths[currentDocID], filesNumber, maximumAllowableErrorsNumber,
                                                                                    packageID, messageOneFile, messageMultipleFiles, errorLevelOneFile, errorLevelMultipleFiles)};
        //Скопировать (переместить) результаты в контейнер прочитанных документов
        documents.first[currentDocID] = std::move(tmp.first);
        documents.second[currentDocID] = tmp.second;std::cout << '\n' << "currentDocID: " << currentDocID << '\n';
    }

    //Вернуть прочитанные документы
    return documents;
}



//0.1. Проверить функцию на успешность чтения всех документов без проверки кодов ошибок.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, allDocumentsReadSuccessfullyWithoutCheckErrorCodes)
{
    //Обнулить результат операции
    bool result{};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths(), Bases::paths().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_0(), ProgramArguments::packageID_0(),
                                                                                                                "", "", ErrorLevel::warning, ErrorLevel::error);

    //Все ли документы успешно прочитаны
    result = textsAndErrorCodes.first == Bases::documents();

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//0.2. Проверить функцию на успешность чтения всех документов с проверкой кодов ошибок.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, allDocumentsReadSuccessfullyWithCheckErrorCodes)
{
    //Обнулить результат операции
    bool result{};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths(), Bases::paths().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_0(), ProgramArguments::packageID_0(),
                                                                                                                "", "", ErrorLevel::warning, ErrorLevel::error);

    //Все ли документы успешно прочитаны
    result = textsAndErrorCodes.first == Bases::documents();

    //Для каждого кода ошибки
    for (auto& errorCode : textsAndErrorCodes.second)
    {
        //Если ошибка есть
        if (errorCode != ErrorCode::no_error)
        {
            result = false;
            break;
        }
    }

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//0.3. Проверить функцию на успешность чтения всех документов без проверки кодов ошибок. Два документа отсутствуют.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, notAllDocumentsReadSuccessfullyWithoutCheckErrorCodes)
{
    //Обнулить результат операции
    bool result{};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                "", "", ErrorLevel::warning, ErrorLevel::error);

    //Все ли документы успешно прочитаны
    result = textsAndErrorCodes.first == Bases::documents_file001_002_missing();

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//0.4. Проверить функцию на успешность чтения всех документов с проверкой кодов ошибок. Два документа отсутствуют.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, notAllDocumentsReadSuccessfullyWithCheckErrorCodes)
{
    //Обнулить результат операции
    bool result{};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                "", "", ErrorLevel::warning, ErrorLevel::error);

    //Все ли документы успешно прочитаны
    result = textsAndErrorCodes.first == Bases::documents_file001_002_missing();

    //Счётчик ошибок
    std::size_t countError{};

    //Для каждого кода ошибки
    for (auto& errorCode : textsAndErrorCodes.second)
    {
        //Если ошибка есть
        if (errorCode != ErrorCode::no_error)
        {
            ++countError;
        }
    }

    //Количество ошибок должно совпадать с количеством отсутствующих файлов
    result = result && countError == ProgramArguments::maximumAllowableErrorsNumber_2();

    //Проверить утверждение
    ASSERT_TRUE(result);
}



//Проверка, когда уровни логирования указываются при вызове функции

//1. Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalFewerErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';
    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::fatal);

    //Ожидать записи в файл
    waitFileWrite(ProgramArguments::waitFileWrite_micro_10());
    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//2. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalFewerErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//3. Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalFewerErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::fatal);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//4. Проверить функцию на уровень логирования. Ошибок меньше, для каждого warning, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorFewerErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles, ErrorLevel::warning, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_warning());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//5. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorFewerErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::error);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }


    //Ожидать записи в файл
    waitFileWrite(ProgramArguments::waitFileWrite_micro_10());
    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//6. Проверить функцию на уровень логирования. Ошибок меньше, для каждого warning, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorFewerErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles, ErrorLevel::warning, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_warning(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//7. Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';
    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов и было исключение
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//8. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов и было исключение
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//9. Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalMoreErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла и было исключение
    result = result && isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), Bases::paths_files_all_missing().size());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//10. Проверить функцию на уровень логирования. Ошибок больше, для каждого warning, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles, ErrorLevel::warning, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//11. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::error);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }


    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//12. Проверить функцию на уровень логирования. Ошибок больше, для каждого warning, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorMoreErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles, ErrorLevel::warning, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_warning(), Bases::paths_files_all_missing().size());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//13. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalFewerErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//14. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalMoreErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::fatal);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла и было исключение
    result = result && isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), Bases::paths_files_all_missing().size());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//15. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorFewerErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::error);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//16. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorMoreErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::error);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла и было исключение
    result = result && isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), Bases::paths_files_all_missing().size());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//Проверка, когда уровни логирования указываются при вызове функции



//Проверка, когда уровни логирования указываются в контейнере соответствия имени вызывающей функции и уровня логирования

//17. Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//18. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//19. Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalFewerErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//20. Проверить функцию на уровень логирования. Ошибок меньше, для каждого warning, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::warning;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_warning());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//21. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//22. Проверить функцию на уровень логирования. Ошибок меньше, для каждого warning, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorFewerErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::warning;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_warning(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//23. Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов и было исключение
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//24. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов и было исключение
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//25. Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, errorFatalMoreErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла и было исключение
    result = result && isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), Bases::paths_files_all_missing().size());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//26. Проверить функцию на уровень логирования. Ошибок больше, для каждого warning, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::warning;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//27. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//28. Проверить функцию на уровень логирования. Ошибок больше, для каждого warning, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, warningErrorMoreErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::warning;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов последовательно
    std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_warning(), Bases::paths_files_all_missing().size());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//29. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalFewerErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//30. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalFatalMoreErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла и было исключение
    result = result && isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), Bases::paths_files_all_missing().size());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//31. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorFewerErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_file001_002_missing(), Bases::paths_file001_002_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//32. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFilesSequentially, fatalErrorMoreErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов последовательно
        std::pair <std::vector<std::string>, std::vector<ErrorCode>> textsAndErrorCodes = readFilePathsSequentially(Bases::paths_files_all_missing(), Bases::paths_files_all_missing().size(),
                                                                                                                    ProgramArguments::maximumAllowableErrorsNumber_2(), ProgramArguments::packageID_0(),
                                                                                                                    timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла и было исключение
    result = result && isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_fatal(), Bases::paths_files_all_missing().size());

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readMultipleTextFilesSequentially"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFilesSequentially"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}//Проверка, когда уровни логирования указываются в контейнере соответствия имени вызывающей функции и уровня логирования
