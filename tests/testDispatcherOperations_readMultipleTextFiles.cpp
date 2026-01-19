//
// Created by Alexander on 17.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции readMultipleTextFiles

/**
      * Прочитать несколько текстовых файлов одновременно в разных потоках
      * @param filePaths Ссылка на путь контейнера путей файлов
      * @param desiredNumberOfThreads Желаемое количество потоков
      * @param maximumAllowableErrorsNumber Максимально возможное количество ошибок
      * @param messageOneFile Ссылка на сообщение для каждого файла
      * @param messageMultipleFiles Ссылка на сообщение для всех файлов
      * @param errorLevelOneFile Уровень логирования для одного фойла
      * @param errorLevelMultipleFiles Уровень логирования для всех файлов
      * @param callingFunction Ссылка на вызывающую функцию
      * @return Структура результатов чтения текстовых файлов
      */
ResultOfReadMultipleTextFiles testReadMultipleTextFiles(
        const std::vector<std::string> &filePaths,
        const unsigned int desiredNumberOfThreads = std::thread::hardware_concurrency(),
        const std::size_t maximumAllowableErrorsNumber = 0,
        const std::string& messageOneFile = "", const std::string& messageMultipleFiles = "",
        ErrorLevel errorLevelOneFile = ErrorLevel::no_level, ErrorLevel errorLevelMultipleFiles = ErrorLevel::no_level,
        const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION)
{
    //Прочитать документы
    return DispatcherOperations::readMultipleTextFiles(filePaths, desiredNumberOfThreads, maximumAllowableErrorsNumber,
                                                       messageOneFile, messageMultipleFiles, errorLevelOneFile, errorLevelMultipleFiles);
}



//Проверка, когда уровни логирования указываются при вызове функции

//1. Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalFewerErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::fatal);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//2. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalFatalFewerErrorsForAllFiles)
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
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
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
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalFewerErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::fatal);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//4. Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorFewerErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//5. Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalErrorFewerErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                                timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//6. Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorFewerErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//7. Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
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
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalFatalMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
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
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalMoreErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
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

//10. Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//11. Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalErrorMoreErrorsForAllFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';
    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles, ErrorLevel::fatal, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//12. Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorMoreErrorsForEachFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles, ErrorLevel::error, ErrorLevel::error);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), Bases::paths_files_all_missing().size());

    //Проверить утверждение
    ASSERT_TRUE(result);
}//Проверка, когда уровни логирования указываются при вызове функции



//Проверка, когда уровни логирования указываются в контейнере соответствия имени вызывающей функции и уровня логирования

//Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalFatalFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';

    try
    {
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                                timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::error;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalFewerErrorsForEachFileWithoutErrorLevel)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок меньше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalErrorFewerErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок меньше, для каждого error, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorFewerErrorsForEachFileWithoutErrorLevel)
{

    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
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

//Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех fatal, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalFatalMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::fatal;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                                timePointForEachFile, timePointForAllFiles);
    }
    catch (const DispatcherOperations::OperationException& exception)
    {
        result = true;
    }

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов и было исключение
    result = result && isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_fatal());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::error;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех fatal, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalMoreErrorsForEachFileWithoutErrorLevel)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    try
    {
        //Прочитать несколько текстовых файлов одновременно в разных потоках
        ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
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

//Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок больше, для каждого fatal, для всех error, сообщение для всех.
TEST(TestDispatcherOperations_readMultipleTextFiles, fatalErrorMoreErrorsForAllFilesWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::fatal;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};
    std::cout << timePointForEachFile << ' ' << timePointForAllFiles << '\n';
    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для всех файлов
    result = isMatchingErrorLevel(timePointForAllFiles, ProgramArguments::errorLevel_error());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["DispatcherOperations::readTextFileFromMultipleFiles"] = ErrorLevel::error;
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования. Ошибок больше, для каждого error, для всех error, сообщение для каждого.
TEST(TestDispatcherOperations_readMultipleTextFiles, errorErrorMoreErrorsForEachFileWithoutErrorLevel)
{
    //Установить вызывающую функцию в нужный уровень логирования в контейнере соответствия
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::error;

    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointForEachFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointForAllFiles{getTimePoint()};

    //Прочитать несколько текстовых файлов одновременно в разных потоках
    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = testReadMultipleTextFiles(Bases::paths_files_all_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                            timePointForEachFile, timePointForAllFiles);

    //Соответствует ли фактический уровень логирования ожидаемому для каждого файла
    result = isMatchingErrorLevelForEachFile(timePointForEachFile, ProgramArguments::errorLevel_error(), Bases::paths_files_all_missing().size());

    //Вернуть уровень логирования в значение по умолчанию
    DispatcherOperations::getMatchingFunctionNameAndErrorLevel()["testReadMultipleTextFiles"] = ErrorLevel::fatal;

    //Проверить утверждение
    ASSERT_TRUE(result);
}//Проверка, когда уровни логирования указываются в контейнере соответствия имени вызывающей функции и уровня логирования

