//
// Created by AKazmirchuk on 05.02.2026.
//



#include "testGeneral.h"



const std::string& ProgramArguments::nameOfQueue()
{
    //Значение по умолчанию
    static const std::string variable{"search_engine"};
    return variable;
}

boost::interprocess::message_queue::size_type ProgramArguments::maxNumberOfMessages_100()
{
    //Значение по умолчанию
    static const boost::interprocess::message_queue::size_type variable{100};
    return variable;
}

boost::interprocess::message_queue::size_type ProgramArguments::maxMessageSize_1024()
{
    //Значение по умолчанию
    static const boost::interprocess::message_queue::size_type variable{1024};
    return variable;
}

const std::string &ProgramArguments::fileNameOfMonitor()
{
    //Значение по умолчанию
    static const std::string variable{"logger_monitor_test.exe"};
    return variable;
}

const std::string& ProgramArguments::messageDebug()
{
    //Значение по умолчанию
    static const std::string variable{"DEBUG: This is a test message!"};
    return variable;
}

const std::string& ProgramArguments::messageInfo()
{
    //Значение по умолчанию
    static const std::string variable{"INFO: This is a test message!"};
    return variable;
}

const std::string& ProgramArguments::messageWarning()
{
    //Значение по умолчанию
    static const std::string variable{"WARNING: This is a test message!"};
    return variable;
}

const std::string& ProgramArguments::messageError()
{
    //Значение по умолчанию
    static const std::string variable{"ERROR: This is a test message!"};
    return variable;
}

const std::string& ProgramArguments::messageFatal()
{
    //Значение по умолчанию
    static const std::string variable{"FATAL: This is a test message!"};
    return variable;
}

const std::string& ProgramArguments::messageLogger()
{
    //Значение по умолчанию
    static const std::string variable{"LOGGER: This is a test message!"};
    return variable;
}

const std::string& ProgramArguments::messageStop()
{
    //Значение по умолчанию
    static const std::string variable{ProgramArguments::nameOfQueue() + "Stop"};
    return variable;
}

const std::string& ProgramArguments::configLoggerMonitorFilePath()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/messageQueue.json"};
    return variable;
}