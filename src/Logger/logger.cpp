//
// Created by Alexander on 01.04.2025.
//



#include "logger.h"
#include "readWriteJSONFile.h"



void Logger::debug(const std::string& message)
{
    debug(message, ExceptionStub());
}

void Logger::debug(const std::string& message, const std::exception& exception)
{
    log(Level::L_DEBUG_L, message, exception);
}

void Logger::info(const std::string& message)
{
    info(message, ExceptionStub());
}

void Logger::info(const std::string& message, const std::exception& exception)
{
    log(Level::L_INFO_L, message, exception);
}

void Logger::warning(const std::string& message)
{
    warning(message, ExceptionStub());
}

void Logger::warning(const std::string& message, const std::exception& exception)
{
    log(Level::L_WARNING_L, message, exception);
}

void Logger::error(const std::string& message)
{
    error(message, ExceptionStub());
}

void Logger::error(const std::string& message, const std::exception& exception)
{
    log(Level::L_ERROR_L, message, exception);
}

void Logger::fatal(const std::string& message)
{
    fatal(message, ExceptionStub());
}

void Logger::fatal(const std::string& message, const std::exception& exception)
{
    log(Level::L_FATAL_L, message, exception);
}

