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

const std::string& ProgramArguments::configLoggerMonitorFilePathNotExists()
{
    //Значение по умолчанию
    static const std::string variable{"../../tests/resources/messageQueue-notExists.json"};
    return variable;
}

const std::string& ProgramArguments::dateTimeFormat()
{
    //Значение по умолчанию
    static const std::string variable{"%Y-%m-%d %H:%M:%S."};
    return variable;
}

unsigned short ProgramArguments::messageDebugColor()
{
    //Значение по умолчанию
    static const unsigned short variable{7};
    return variable;
}

unsigned short ProgramArguments::messageInfoColor()
{
    //Значение по умолчанию
    static const unsigned short variable{2};
    return variable;
}

unsigned short ProgramArguments::messageWarningColor()
{
    //Значение по умолчанию
    static const unsigned short variable{6};
    return variable;
}

unsigned short ProgramArguments::messageErrorColor()
{
    //Значение по умолчанию
    static const unsigned short variable{4};
    return variable;
}

unsigned short ProgramArguments::messageFatalColor()
{
    //Значение по умолчанию
    static const unsigned short variable{12};
    return variable;
}

unsigned short ProgramArguments::messageLoggerColor()
{
    //Значение по умолчанию
    static const unsigned short variable{3};
    return variable;
}


std::string getLineFromConsole(unsigned long x, unsigned long y, unsigned long length)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string lpCharacter;
    lpCharacter.resize(length);

    COORD dwReadCoord ;
    dwReadCoord.X = x; // Column number
    dwReadCoord.Y = y; // Row number

    DWORD lpNumberOfCharsRead = 0;

    DWORD nLength = length;

    ReadConsoleOutputCharacter(
            hConsoleOutput,
            lpCharacter.data(),
            nLength,
            dwReadCoord ,
            &lpNumberOfCharsRead );

    return lpCharacter;
}

std::vector<WORD> getAttributeFromConsole(unsigned long x, unsigned long y, unsigned long length)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    std::vector<WORD> lpAttribute;
    lpAttribute.resize(length);

    COORD dwReadCoord ;
    dwReadCoord.X = x; // Column number
    dwReadCoord.Y = y; // Row number

    DWORD lpNumberOfAttrsRead = 0;

    DWORD nLength = length;

    ReadConsoleOutputAttribute(
            hConsoleOutput,
            lpAttribute.data(),
            nLength,
            dwReadCoord ,
            &lpNumberOfAttrsRead);

    return lpAttribute;
}

std::pair<unsigned long, unsigned long> getCursorPositionOfConsole()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    COORD dwCursorPosition = csbi.dwCursorPosition;

    SHORT x{dwCursorPosition.X};
    SHORT y{dwCursorPosition.Y};

    return {x, y};
}

unsigned long getLineNumber(const std::string &message)
{
    std::pair<unsigned long, unsigned long> sizeOfConsole{getCursorPositionOfConsole()};

    for (unsigned long currentY{}; currentY < sizeOfConsole.second; ++currentY)
    {
        if (getLineFromConsole(0, currentY, message.size()) == message)
        {
            return currentY;
        }
    }

    return std::numeric_limits<unsigned long>::max();
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