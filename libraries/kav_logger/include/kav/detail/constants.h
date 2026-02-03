//
// Created by Alexander on 25.12.2025.
//

#ifndef KAV_LOGGER_CONSTANTS_H
#define KAV_LOGGER_CONSTANTS_H


#include <stdint.h>
#include <string>



namespace kav
{


/**
 * Класс хранения констант программы
 */
    class Constants
    {

    public:

        Constants() = delete;

        /**
         * Прочитать по умолчанию признак логирования событий в консоль
         * @return Ссылка на переменную
         */
        static const std::string &default_launchConsole()
        {
            //Значение по умолчанию
            static const std::string variable{"yes"};
            return variable;
        }

        /**
         * Прочитать сообщение создания нового лог-файла
         * @return Ссылка на переменную
         */
        static const std::string &messageNewFileCreate()
        {
            //Значение по умолчанию
            static const std::string variable{"The new file was created successfully"};
            return variable;
        }

        /**
         * Прочитать сообщение запуска логгера
         * @return Ссылка на переменную
         */
        static const std::string &messageLoggerStarted()
        {
            //Значение по умолчанию
            static const std::string variable{"The logger was launched successfully"};
            return variable;
        }

        /**
         * Прочитать сообщение запуска логгера
         * @return Ссылка на переменную
         */
        static const std::string &messageLoggerReseted()
        {
            //Значение по умолчанию
            static const std::string variable{"The logger was reseted successfully"};
            return variable;
        }

        /**
         * Прочитать время ожидания
         * @return Ссылка на переменную
         */
        static uint64_t waitTime()
        {
            //Значение по умолчанию
            static const uint64_t variable{10};
            return variable;
        }

    };

}


#endif //KAV_LOGGER_CONSTANTS_H
