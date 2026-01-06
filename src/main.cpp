#include <iostream>

#include "programArguments.h"
#include "searchEngine.h"

#include "kav/logger.h"



/**
 * Запустить расчёт релевантности
 */
void runRelevanceCalculation()
{
    //Создать объект основного класса программы (подготовить входящие данные для выполнения и поиска)
    SearchEngine searchEngine(ProgramArguments::configFilePath(), ProgramArguments::requestsFilePath(), ProgramArguments::answersFilePath(),
                              ProgramArguments::documentsBaseOrPathsBase(),
                              ProgramArguments::precision(),
                              ProgramArguments::formatByWidth(),
                              ProgramArguments::desiredNumberOfThreads(),
                              ProgramArguments::maximumAllowableErrorsNumber());

    //Рассчитать релевантность ответов
    searchEngine.searchModifiedAll();
}

/**
 * Обработать исключения с логированием
 * @param exception Исключение
 */
void handleExceptionsWithLogging(const std::exception& exception)
{
    //Вывести в лог дополнительное сообщение
    kav::Logger::fatal("Early termination of the program!!!", exception);
    //Вывести в лог завершение программы
    kav::Logger::info("Stop SearchEngine");
}

/**
 * Обработать исключения без логирования
 * @param exception Исключение
 */
void handleExceptionsWithoutLogging(const std::exception& exception)
{
    //Вывести сообщение об исключении
    std::cout << "Exception: " << exception.what() << std::endl;
    //Вывести сообщение о завершении работы программы по ошибке
    std::cout << "Stop SearchEngine by error" << std::endl;
}

/**
 * Класс хранения контейнера соответствия имени вызывающей функции и уровня логирования.
 * Означает, что при вызове функций этого класса, уровни логирования прямо указываться не будут
 */
class MatchingFunctionNameAndErrorLevel
{

public:

    MatchingFunctionNameAndErrorLevel() = delete;

    /**
     * Получить ссылку на контейнер соответствия имени вызывающей функции и уровня логирования
     * @return Ссылка на контейнер
     */
    static const std::map<std::string, ErrorLevel> &matchingFunctionNameAndErrorLevel()
    {
        static const std::map<std::string, ErrorLevel> varMatchingFunctionNameAndErrorLevel
        {
                {"ConverterJSON::ConfigConverterJSON::initialize",              ErrorLevel::fatal},
                {"ConverterJSON::checkFilePath",                                ErrorLevel::fatal},
                {"ConverterJSON::checkRequests",                                ErrorLevel::fatal},
                {"DispatcherOperations::readMultipleTextFilesSequentially",     ErrorLevel::error},
                {"InvertedIndex::readDocument",                                 ErrorLevel::fatal},
                {"SearchEngine::readDocsFromFiles",                             ErrorLevel::fatal},
                {"SearchEngine::readDocsFromFilesRef",                          ErrorLevel::fatal},
                {"SearchEngine::writeAnswersToFile",                            ErrorLevel::fatal}
        };

        return varMatchingFunctionNameAndErrorLevel;
    }

};//MatchingFunctionNameAndErrorLevel

int main(int argc, char* argv[])
{
    //Защита от изменения имени файла (так как при инициализации очереди сообщений проверяется этот запущенный процесс)
    //Если имя файла отличное от указанного
    if (std::filesystem::path(argv[0]).filename() != "search_engine.exe")
    {
        //Выйти из программы по ошибке
        return EXIT_FAILURE;
    }

    //Установить соответствия именени вызывающей функции и уровня логирования в программе. Означает, что при вызове функций
    //этого класса, уровни логирования прямо указываться не будут
    DispatcherOperations::setErrorLevelFrom(MatchingFunctionNameAndErrorLevel::matchingFunctionNameAndErrorLevel());

    try
    {
        //Если была вызвана справка
        if (ProcessProgramArguments::processProgramArguments(argc, argv))
        {
            //Выйти из программы по успеху
            return EXIT_SUCCESS;
        }

        //Создать объект логирования событий
        kav::Logger logger(ProgramArguments::configLoggerFilePath(), ProgramArguments::configWriterMessageFilePath(), ProgramArguments::launchConsole());

        try
        {
            //Вывести в лог запуск программы
            kav::Logger::info("------------------------------------------------------------------------");
            kav::Logger::info("Start SearchEngine");

            //Запустить расчёт релевантности
            runRelevanceCalculation();

            //Вывести в лог завершение программы
            kav::Logger::info("Stop SearchEngine");
        }
        //Обработать исключения выброшенные из класса Logger. Эти исключения уже нельзя логировать
        catch (const kav::LoggerException& exception)
        {
            //Обработать исключения без логирования
            handleExceptionsWithoutLogging(exception);

            //Выйти из программы по ошибке
            return EXIT_FAILURE;
        }
        //Обработать все исключения, кроме исключений выброшенных из класса Logger, которые можно логировать
        catch (const std::exception& exception)
        {
            //Обработать исключения с логированием
            handleExceptionsWithLogging(exception);

            //Выйти из программы по ошибке
            return EXIT_FAILURE;
        }
    }
    //Обработать исключения выброшенные из класса Logger и выше. Эти исключения уже нельзя логировать
    catch (const std::exception& exception)
    {
        //Обработать исключения без логирования
        handleExceptionsWithoutLogging(exception);

        //Выйти из программы по ошибке
        return EXIT_FAILURE;
    }

    //Выйти из программы по успеху
    return EXIT_SUCCESS;
}



