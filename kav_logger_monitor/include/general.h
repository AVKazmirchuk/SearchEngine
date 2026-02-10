//
// Created by Alexander on 07.05.2025.
//

#ifndef SEARCH_ENGINE_GENERAL_H
#define SEARCH_ENGINE_GENERAL_H


#include <list>
#include <string>

#include "nlohmann/json.hpp"
#include "kav/operationFileAndJSON.h"



namespace kav
{

//Тип объектов заменён на nlohmann::ordered_json (сохраняет порядок вставки)
//Тип для чисел с плавающей запятой заменён на float
using JSON = nlohmann::basic_json<
        nlohmann::ordered_map,
        std::vector,
        std::string,
        bool,
        std::int64_t,
        std::uint64_t,
        float>;

}

namespace kav
{

    /**
 * Класс реализует генерацию исключений
 */
    class LoggerMonitorException : public std::exception
    {

    public:

        /**
         * Создать объект исключения
         * @param in_errorCode Код ошибки
         * @param in_information Ссылка на информацию по ошибке
         */
        explicit LoggerMonitorException(ErrorCode in_errorCode, const std::string &in_information = "") : errorCode{
                in_errorCode}
        {
            information = DescriptionErrorCode::descriptionErrorCode(errorCode) + ": " + in_information;
        }

        /**
         * Получить информацию по исключению
         * @return Информация по исключению
         */
        [[nodiscard]] const char *what() const noexcept override
        {
            return information.c_str();
        }

        /**
         * Получить код исключения
         * @return Код исключения
         */
        [[nodiscard]] ErrorCode getErrorCode() const
        {
            //Вернуть код ошибки
            return errorCode;
        }

    private:

        //Код ошибки
        ErrorCode errorCode;
        //Информация по ошибке
        std::string information;

    };

}



#endif //SEARCH_ENGINE_GENERAL_H
