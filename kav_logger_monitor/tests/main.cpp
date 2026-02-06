//
// Created by Alexander on 30.03.2025.
//



//#include "gtest/gtest.h"

#include <future>
#include <thread>

#include "testGeneral.h"


void runLoggerMonitor(kav::LoggerMonitor& loggerMonitor)
{
    //Запустить монитор
    loggerMonitor.run();


}

/*void kav::Logger::WriterMessage::startMonitor(LPCSTR lpApplicationName)
{
    //Дополнительная информация
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    //Установить размеры структур
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );


    //Запустить независимый процесс
    if( !CreateProcess( lpApplicationName,   // No module name (use command line)
                        nullptr,        // Command line
                        nullptr,           // Process handle not inheritable
                        nullptr,           // Thread handle not inheritable
                        FALSE,          // Set handle inheritance to FALSE
                        CREATE_NEW_CONSOLE,              // No creation flags
                        nullptr,           // Use parent's environment block
                        nullptr,           // Use parent's starting directory
                        &si,            // Pointer to STARTUPINFO structure
                        &pi )           // Pointer to PROCESS_INFORMATION structure
            )
    {
        //printf( "CreateProcess failed (%d).\n", GetLastError() );
        //return;
    }

    // Wait until child process exits.
    //WaitForSingleObject( pi.hProcess, INFINITE );

    //TODO проверить закрытие дескрипторов

    // Close process and thread handles.
    //CloseHandle( pi.hProcess );
    //CloseHandle( pi.hThread );
}*/

std::string getLineFromConsole(int x, int y)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    std::string lpCharacter;
    lpCharacter.resize(32);

    COORD dwReadCoord ;
    dwReadCoord.X = x; // Column number
    dwReadCoord.Y = y; // Row number

    DWORD lpNumberOfCharsRead  = 0;

    DWORD nLength = 32;

    ReadConsoleOutputCharacter(
            hConsoleOutput,
            lpCharacter.data(),
            nLength,
            dwReadCoord ,
            &lpNumberOfCharsRead );

    return lpCharacter;
}

std::vector<WORD> getAttributeFromConsole(int x, int y)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    std::vector<WORD> lpAttribute;
    lpAttribute.resize(32);

    COORD dwReadCoord ;
    dwReadCoord.X = x; // Column number
    dwReadCoord.Y = y; // Row number

    DWORD lpNumberOfAttrsRead  = 0;

    DWORD nLength = 32;

    ReadConsoleOutputAttribute(
            hConsoleOutput,
            lpAttribute.data(),
            nLength,
            dwReadCoord ,
            &lpNumberOfAttrsRead);

    return lpAttribute;
}

int main()
{


    //Обнулить результат операции
    bool result{};

    //Удалить оставшуюся очередь (скорее всего, заблокированную)
    boost::interprocess::message_queue::remove(ProgramArguments::nameOfQueue().c_str());
    std::cout << "The queue has left" << '\n';

    //Сначала надо запустить монитор. Если наоборот, - запись и чтение очереди не работает.

    //Создать объект класса логирования событий в монитор
    kav::LoggerMonitor loggerMonitor(ProgramArguments::configLoggerMonitorFilePath());

    std::future<void> fut = std::async(&runLoggerMonitor, std::ref(loggerMonitor));



    //Объект очереди сообщений для отправки
    MonitorSender monitorSender(ProgramArguments::nameOfQueue(), ProgramArguments::maxNumberOfMessages_100(),
                                ProgramArguments::maxMessageSize_1024(), ProgramArguments::fileNameOfMonitor());

    monitorSender.send(ProgramArguments::messageDebug());

    while (loggerMonitor.getLastMessageReceived() == "")
    {
        //std::cout << "getLastMessageReceived: " << loggerMonitor.getLastMessageReceived() << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //monitorSender.send(ProgramArguments::message());
    }


    //monitorSender.send(ProgramArguments::message());

    if (loggerMonitor.getLastMessageReceived() == ProgramArguments::messageDebug())
    {
        result = true;
    }

    //monitorSender.send(ProgramArguments::messageDebug());
    //monitorSender.send(ProgramArguments::messageInfo());
    monitorSender.send(ProgramArguments::messageWarning());
    //monitorSender.send(ProgramArguments::messageError());
    //monitorSender.send(ProgramArguments::messageFatal());
    //monitorSender.send(ProgramArguments::messageLogger());

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "getLineFromConsole: " << getLineFromConsole(0, 14) << '\n';
    std::cout << "getAttributeFromConsole:" << '\n';

    for (auto& elem : getAttributeFromConsole(0, 14))
    {
        std::cout << elem << " ";
    }
    std::cout << '\n';

    monitorSender.send(ProgramArguments::messageStop());

    fut.get();


    std::cout << "result: " << result;

    //Запустить все тесты
    //::testing::InitGoogleTest();
    //return RUN_ALL_TESTS();
std::getchar();
    return 0;
}



//https://stackoverflow.com/questions/52539568/how-i-can-read-simply-console-output