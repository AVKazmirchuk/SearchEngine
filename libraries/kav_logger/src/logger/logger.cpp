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
    //Изменить конфигурацию логгера
    ptrToLogger->configLogger.reset(in_configLoggerFilePath);

    //Настроить класс
    ptrToLogger->setup();
}

bool kav::Logger::isMessageRecorded()
{
    return ptrToLogger->recordingMessage.load();
}

/*const std::filesystem::path& kav::Logger::getCurrentLogPath()
{
    return ptrToLogger->file;
}*/