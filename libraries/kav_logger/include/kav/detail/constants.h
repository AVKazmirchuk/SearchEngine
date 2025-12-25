//
// Created by Alexander on 25.12.2025.
//

#ifndef SEARCH_ENGINE_SOLUTION_CONSTANTS_H
#define SEARCH_ENGINE_SOLUTION_CONSTANTS_H



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

    };

}


#endif //SEARCH_ENGINE_SOLUTION_CONSTANTS_H
