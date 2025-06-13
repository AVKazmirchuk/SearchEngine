//
// Created by Alexander on 01.04.2025.
//



#include "logger.h"
#include "check/operationFileAndJSON.h"



void Logger::debug(const std::string& message)
{
    debug(message, ExceptionStub());
}

void Logger::debug(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::debug, message, exception);
}

void Logger::info(const std::string& message)
{
    info(message, ExceptionStub());
}

void Logger::info(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::info, message, exception);
}

void Logger::warning(const std::string& message)
{
    warning(message, ExceptionStub());
}

void Logger::warning(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::warning, message, exception);
}

void Logger::error(const std::string& message)
{
    error(message, ExceptionStub());
}

void Logger::error(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::error, message, exception);
}

void Logger::fatal(const std::string& message)
{
    fatal(message, ExceptionStub());
}

void Logger::fatal(const std::string& message, const std::exception& exception)
{
    ptrToLogger->log(Level::fatal, message, exception);
}

