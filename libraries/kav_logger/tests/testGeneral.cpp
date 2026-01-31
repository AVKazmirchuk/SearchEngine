//
// Created by Alexander on 24.01.2026.
//



#include "testGeneral.h"



const std::string& ProgramArguments::configFilePath()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test.json"};
    return variable;
}

const std::string& ProgramArguments::configFilePath_2()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-2.json"};
    return variable;
}

const std::string& ProgramArguments::configFilePath_missing()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-missing.json"};
    return variable;
}

const std::string& ProgramArguments::configFilePath_filesEmpty()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-files-empty.json"};
    return variable;
}

const std::string& ProgramArguments::configFilePath_file003_missing()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/config-test-file003-missing.json"};
    return variable;
}

const std::string& ProgramArguments::requestsFilePath()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/requests-test.json"};
    return variable;
}

const std::string& ProgramArguments::requestsFilePath_missing()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/requests-test-missing.json"};
    return variable;
}

const std::string& ProgramArguments::requestsFilePath_requestsEmpty()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/requests-test-requests-empty.json"};
    return variable;
}

const std::string& ProgramArguments::answersFilePath()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/answers-test.json"};
    return variable;
}

const std::string& ProgramArguments::readJSONFile()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/readJSONFile.json"};
    return variable;
}

const std::string& ProgramArguments::readMissingJSONFile()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/readJSONFile-missing.json"};
    return variable;
}

const std::string& ProgramArguments::readTextFile()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/readTextFile.txt"};
    return variable;
}

const std::string& ProgramArguments::readMissingTextFile()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/readTextFile-missing.txt"};
    return variable;
}

const std::string& ProgramArguments::checkRequestsArray()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/checkRequestsArray.json"};
    return variable;
}

const std::string& ProgramArguments::answersFilePath_empty()
{
    //Значение по умолчанию
    static const std::string variable;
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_usage_1sec()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-usage-1sec.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_usage_3sec()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-usage-3sec.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_storage_3sec()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-storage-3sec.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_usage_6sec_in_minutes()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-usage-6sec-in-minutes.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_storage_6sec_in_minutes()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-storage-6sec-in-minutes.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_usage_6sec_in_hours()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-usage-6sec-in-hours.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_storage_6sec_in_hours()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-storage-6sec-in-hours.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_usage_6sec_in_days()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-usage-6sec-in-days.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_storage_6sec_in_days()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-storage-6sec-in-days.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_usage_6sec_in_weeks()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-usage-6sec-in-weeks.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_storage_6sec_in_weeks()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-storage-6sec-in-weeks.json"};
    return variable;
}

const std::string& ProgramArguments::configLoggerFilePath_size_100_bytes()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/logger-size-100-bytes.json"};
    return variable;
}

const std::string& ProgramArguments::configWriterMessageFilePath()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/messageQueue.json"};
    return variable;
}

const std::string& ProgramArguments::logsFolderName()
{
    //Значение по умолчанию
    static const std::string variable{"Logs"};
    return variable;
}

const std::string& ProgramArguments::jsonFileName()
{
    //Значение по умолчанию
    static const std::string variable{"writeJSONFile.json"};
    return variable;
}

const std::string& ProgramArguments::messageForException()
{
    //Значение по умолчанию
    static const std::string variable{"This is a test message for an exception"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_debug()
{
    //Значение по умолчанию
    static const std::string variable{"DEBUG"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_info()
{
    //Значение по умолчанию
    static const std::string variable{"INFO"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_warning()
{
    //Значение по умолчанию
    static const std::string variable{"WARNING"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_error()
{
    //Значение по умолчанию
    static const std::string variable{"ERROR"};
    return variable;
}

const std::string& ProgramArguments::errorLevel_fatal()
{
    //Значение по умолчанию
    static const std::string variable{"FATAL"};
    return variable;
}

const std::string& ProgramArguments::dateTimeFormat()
{
    //Значение по умолчанию
    static const std::string variable{"%Y-%m-%d %H:%M:%S."};
    return variable;
}

const std::string& ProgramArguments::launchConsole_yes()
{
    //Значение по умолчанию
    static const std::string variable{"yes"};
    return variable;
}

const std::string& ProgramArguments::launchConsole_no()
{
    //Значение по умолчанию
    static const std::string variable{"no"};
    return variable;
}

int ProgramArguments::size_100()
{
    //Значение по умолчанию
    static const int variable{200};
    return variable;
}

int ProgramArguments::numberFiles_3()
{
    //Значение по умолчанию
    static const int variable{3};
    return variable;
}

std::chrono::microseconds ProgramArguments::waitFileWrite_micro_10()
{
    //Значение по умолчанию
    static const std::chrono::microseconds variable{10};
    return variable;
}

std::chrono::seconds ProgramArguments::seconds_1()
{
    //Значение по умолчанию
    static const std::chrono::seconds variable{1};
    return variable;
}

std::chrono::seconds ProgramArguments::seconds_3()
{
    //Значение по умолчанию
    static const std::chrono::seconds variable{3};
    return variable;
}

std::chrono::duration<double, std::ratio<60>> ProgramArguments::seconds_6_in_minutes()
{
    //Значение по умолчанию
    static const std::chrono::duration<double, std::ratio<60>> variable{0.1};
    return variable;
}

std::chrono::duration<double, std::ratio<60 * 60>> ProgramArguments::seconds_6_in_hours()
{
    //Значение по умолчанию
    static const std::chrono::duration<double, std::ratio<60 * 60>> variable{0.0017};
    return variable;
}

std::chrono::duration<double, std::ratio<60 * 60 * 24>> ProgramArguments::seconds_6_in_days()
{
    //Значение по умолчанию
    static const std::chrono::duration<double, std::ratio<60 * 60 * 24>> variable{0.000069};
    return variable;
}

std::chrono::duration<double, std::ratio<60 * 60 * 24 * 7>> ProgramArguments::seconds_6_in_weeks()
{
    //Значение по умолчанию
    static const std::chrono::duration<double, std::ratio<60 * 60 * 24 * 7>> variable{0.0000099};
    return variable;
}

const unsigned int& ProgramArguments::precision()
{
    //Значение по умолчанию
    static const unsigned int variable{6};
    return variable;
}

const unsigned int& ProgramArguments::precision_3()
{
    //Значение по умолчанию
    static const unsigned int variable{3};
    return variable;
}

const int& ProgramArguments::formatByWidth()
{
    //Значение по умолчанию
    static const int variable{2};
    return variable;
}

unsigned int ProgramArguments::desiredNumberOfThreads()
{
    //Значение по умолчанию
    static const unsigned int variable{std::thread::hardware_concurrency() - 1};
    return variable;
}

unsigned int ProgramArguments::desiredNumberOfThreads_1()
{
    //Значение по умолчанию
    static const unsigned int variable{1};
    return variable;
}

unsigned int ProgramArguments::desiredNumberOfThreads_3()
{
    //Значение по умолчанию
    static const unsigned int variable{3};
    return variable;
}

const std::size_t& ProgramArguments::maximumAllowableErrorsNumber_0()
{
    //Значение по умолчанию
    static const std::size_t variable{0};
    return variable;
}

const std::size_t& ProgramArguments::maximumAllowableErrorsNumber_1()
{
    //Значение по умолчанию
    static const std::size_t variable{1};
    return variable;
}

const std::size_t& ProgramArguments::maximumAllowableErrorsNumber_2()
{
    //Значение по умолчанию
    static const std::size_t variable{2};
    return variable;
}

const std::size_t& ProgramArguments::packageID_0()
{
    //Значение по умолчанию
    static const std::size_t variable{0};
    return variable;
}

unsigned int ProgramArguments::maxResponses()
{
    //Значение по умолчанию
    static const unsigned int variable{5};
    return variable;
}



std::string getLastFilePath()
{
    //Подготовить переменные
    std::filesystem::directory_entry directoryEntry;
    std::chrono::system_clock::time_point timePoint{};

    //Для каждого файла директории
    for (const auto& currentDirectoryEntry : std::filesystem::directory_iterator(ProgramArguments::logsFolderName()))
    {
        //Преобразовать время в нужный тип
        std::chrono::system_clock::time_point currentTimePoint{std::chrono::clock_cast<std::chrono::system_clock>(currentDirectoryEntry.last_write_time())};
        //Если время изменения текущего файла позже
        if (currentTimePoint > timePoint)
        {
            //Запомнить файл
            directoryEntry = currentDirectoryEntry;
        }
    }

    //Вернуть путь файла
    return directoryEntry.path().string();
    //return kav::Logger::getCurrentLogPath().string();
}

std::string timePointToString(const std::chrono::system_clock::time_point& now)
{
    //Преобразовать момент времени в объект времени POSIX
    std::time_t t{std::chrono::system_clock::to_time_t(now)};

    //Задать размер строки
    std::string ts(256,0);

    //Преобразовать время в строку, и задать размер строки
    ts.resize(std::strftime(&ts[0], ts.size(), ProgramArguments::dateTimeFormat().c_str(), std::localtime(&t)));

    //Преобразовать момент времени в секунды
    std::chrono::system_clock::time_point nowSeconds{std::chrono::time_point_cast<std::chrono::seconds>(now)};

    //Получить наносекунды
    std::chrono::nanoseconds nanoseconds{now - nowSeconds};

    //Преобразовать наносекунды в строку
    std::stringstream ss4;
    ss4 << nanoseconds.count();
    std::string strNanosecondsCount;
    ss4 >> strNanosecondsCount;

    //Вернуть строку времени
    return ts + strNanosecondsCount;
}

std::string  getTimePoint()
{
    //Получить текущий момент времени
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};

    //Отметка времени
    std::string timePoint{timePointToString(now)};

    return timePoint;
}

//Получить строку лог-файл
std::string getLogLine(const std::string& timePoint)
{
    //Получить путь текущего лог-файла
    std::string fileName{getLastFilePath()};std::cout << '\n' << "fileName: " << fileName << '\n';

    std::ofstream out(fileName, std::ios::app);
    out << "\n--- New Test ---\n";
    out.close();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    //Прочитать лог-файл
    std::string log{kav::OperationFileAndJSON::readTextFile(fileName).first};

    //Обнулить результат операции
    bool result{};

    //Определить позицию отметки времени в лог-файле
    std::string::size_type found{log.rfind(timePoint)};

    //Строка лог-файла
    std::string logLine{""};

    //Если отметка присутствует
    if (found != std::string::npos)
    {
        //Определить начало строки с отметкой в лог-файле
        std::string::size_type begin{log.rfind('\n', found)};
        //Если это начало файла
        if (begin == std::string::npos) begin = 0;

        //Определить конец строки с отметкой в лог-файле
        std::string::size_type end{log.find('\n', found)};
        //Если это конец файла
        if (end == std::string::npos) end = log.size() - 1;

        //Выделить строку сообщения с отметкой
        logLine = log.substr(begin + 1, end - begin - 1);
    }

    return logLine;
}

bool isMatchingErrorLevel(const std::string& timePoint, const std::string& strErrorLevel)
{
    //Обнулить результат операции
    bool result{};

    //Строка лог-файла
    std::string logLine{getLogLine(timePoint)};

    //Если уровень логирования совпадает
    if (logLine.find(strErrorLevel) != std::string::npos)
    {
        //Установить результат операции
        result = true;
    }

    //Возвратить результат операции
    return result;
}

bool isMatchingErrorLevelForException(const std::string& timePoint, const std::string& message, const std::string& strErrorLevel)
{
    //Обнулить результат операции
    bool result{};

    //Соответствует ли фактический уровень логирования ожидаемому
    std::string logLine{getLogLine(timePoint)};

    //Если уровень логирования совпадает
    if (logLine.find(strErrorLevel) != std::string::npos)
    {
        //Установить результат операции
        result = true;
    }

    //Если сообщение для исключения не присутствует
    if (logLine.find(message) == std::string::npos)
    {
        //Установить результат операции
        result = false;
    }

    //Возвратить результат операции
    return result;
}

std::chrono::system_clock::time_point getTimePointFromString(std::string& strLogLine)
{
    //Объявить переменные
    std::string dateFirstEntry, timeFirstEntry;
    std::stringstream ss{strLogLine};
    //Прочитать дату и время первой записи в файле
    ss >> dateFirstEntry >> timeFirstEntry;

    //Преобразовать строки даты и времени, прочитанных из файла, в удобный формат времени для дальнейшего использования
    std::tm tm{};
    std::istringstream iss{dateFirstEntry + ' ' + timeFirstEntry};
    iss >> std::get_time(&tm, ProgramArguments::dateTimeFormat().c_str());
    std::time_t tt{std::mktime(&tm)};
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::from_time_t(tt)};

    //Определить подстроку с наносекундами
    std::string strNanoseconds{timeFirstEntry.substr(timeFirstEntry.find('.') + 1)};

    //Получить из подстроки наносекунды
    std::chrono::nanoseconds nanoseconds{std::stoull(strNanoseconds)};

    //Получить момент времени с наносекундами
    return tp + nanoseconds;
}

std::chrono::system_clock::time_point getTimePointFromFile(std::string& fileName)
{
    std::ifstream inFile(fileName);
    std::string logLine;
    std::getline(inFile, logLine);
    std::cout << logLine;
    return getTimePointFromString(logLine);
}