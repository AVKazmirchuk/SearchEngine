//
// Created by Alexander on 01.04.2025.
//



#include "kav/logger.h"
#include "kav/operationFileAndJSON.h"



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

