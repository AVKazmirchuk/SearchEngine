//
// Created by Alexander on 01.04.2025.
//



#include "kav/logger.h"
#include "kav/operationFileAndJSON.h"



void kav::Logger::logger(const std::string &message)
{
    logger(message, ExceptionStub());
}

void kav::Logger::logger(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::logger, message, exception);
}

void kav::Logger::debug(const std::string& message)
{
    debug(message, ExceptionStub());
}

void kav::Logger::debug(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::debug, message, exception);
}

void kav::Logger::info(const std::string& message)
{
    info(message, ExceptionStub());
}

void kav::Logger::info(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::info, message, exception);
}

void kav::Logger::warning(const std::string& message)
{
    warning(message, ExceptionStub());
}

void kav::Logger::warning(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::warning, message, exception);
}

void kav::Logger::error(const std::string& message)
{
    error(message, ExceptionStub());
}

void kav::Logger::error(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::error, message, exception);
}

void kav::Logger::fatal(const std::string& message)
{
    fatal(message, ExceptionStub());
}

void kav::Logger::fatal(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::fatal, message, exception);
}

void kav::Logger::reset(const std::string &in_configLoggerFilePath)
{
    std::cout << '\n' << "reset" << '\n';
    while (ptrToLogger->recordingMessage.load())
    {
        //Ожидать
        std::this_thread::sleep_for(std::chrono::microseconds(Constants::waitTime()));
    }

    //Изменить конфигурацию логгера
    ptrToLogger->configLogger.reset(in_configLoggerFilePath);

    //Настроить класс
    ptrToLogger->setup();

    //Записать сообщение уровня logger
    logger(Constants::messageLoggerReseted());
}

bool kav::Logger::isMessageRecorded()
{
    return ptrToLogger->recordingMessage.load();
}

std::chrono::system_clock::time_point kav::Logger::getTimePointFromString(std::string& strLogLine)
{
    //Объявить переменные
    std::string dateFirstEntry, timeFirstEntry;
    std::stringstream ss{strLogLine};
    //Прочитать дату и время первой записи в файле
    ss >> dateFirstEntry >> timeFirstEntry;

    //Преобразовать строки даты и времени, прочитанных из файла, в удобный формат времени для дальнейшего использования
    std::tm tm{};
    std::istringstream iss{dateFirstEntry + ' ' + timeFirstEntry};
    iss >> std::get_time(&tm, configLogger.dateTimeFormat().c_str());

    //Если произошла ошибка
    if (iss.fail())
    {
        //Вернуть начало эпохи
        return {};
    }

    std::time_t tt{std::mktime(&tm)};
    std::chrono::system_clock::time_point tp{std::chrono::system_clock::from_time_t(tt)};

    //Определить подстроку с наносекундами
    std::string strNanoseconds{timeFirstEntry.substr(timeFirstEntry.find('.') + 1)};

    unsigned long long nanosecondsElementary{};

    try
    {
        //Получить из подстроки наносекунды
        nanosecondsElementary = std::stoull(strNanoseconds);
    }
    catch (const std::exception& exception)
    {
        //Вернуть начало эпохи
        return {};
    }

    //Получить из подстроки наносекунды
    std::chrono::nanoseconds nanoseconds{nanosecondsElementary};

    //Получить момент времени с наносекундами
    return tp + nanoseconds;
}

void kav::Logger::handleErrorReadingLogFile(const std::filesystem::path &path)
{
    //Удалить текущий файл из директории. Пока ничего другого не придумал
    std::filesystem::remove(path);
}

/*const std::filesystem::path& kav::Logger::getCurrentLogPath()
{
    return ptrToLogger->file;
}*/