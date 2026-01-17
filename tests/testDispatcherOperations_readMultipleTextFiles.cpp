//
// Created by Alexander on 17.01.2026.
//



#include "gtest/gtest.h"

#include "dispatcherOperations.h"

#include "testGeneral.h"



//Тестирование функции readMultipleTextFiles
//Прочитать документы
ResultOfReadMultipleTextFiles readDocsFromFiles(
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

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalMultipleFiles)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointOneFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointMultipleFiles{getTimePoint()};

    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = readDocsFromFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                    timePointOneFile, timePointMultipleFiles, ErrorLevel::error, ErrorLevel::fatal);

    result = isMatchingErrorLevel(timePointMultipleFiles, ProgramArguments::errorLevel_error());

    //Проверить утверждение
    ASSERT_TRUE(result);
}

//Проверить функцию на уровень логирования debug
TEST(TestDispatcherOperations_readMultipleTextFiles, errorFatalOneFile)
{
    //Обнулить результат операции
    bool result{};

    //Отметка времени для каждого файла
    std::string timePointOneFile{getTimePoint()};

    //Отметка времени для всех файлов
    std::string timePointMultipleFiles{getTimePoint()};

    ResultOfReadMultipleTextFiles resultOfReadMultipleTextFiles = readDocsFromFiles(Bases::paths_file001_002_missing(), ProgramArguments::desiredNumberOfThreads(), ProgramArguments::maximumAllowableErrorsNumber_2(),
                                                                                    timePointOneFile, timePointMultipleFiles, ErrorLevel::error, ErrorLevel::fatal);

    result = isMatchingErrorLevelForEachFile(timePointOneFile, ProgramArguments::errorLevel_error(), ProgramArguments::maximumAllowableErrorsNumber_2());

    //Проверить утверждение
    ASSERT_TRUE(result);
}