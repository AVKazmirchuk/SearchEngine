//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_OPERATIONFILEANDJSON_H
#define SEARCH_ENGINE_OPERATIONFILEANDJSON_H



#include <fstream>
#include <string>

#include "boost/assert/source_location.hpp"
#include "nlohmann/json.hpp"

#include "kav/detail/errorCode.h"
#include "kav/detail/types.h"



namespace kav
{

    /**
     * Класс реализует проверку соответствия JSON-структуры шаблону
     */
    class CheckJSON
    {

    public:

        CheckJSON() = delete;

        /**
         * Проверить JSON-структуру на соответствие шаблону
         * @param objectJSON JSON-объект проверяемого
         * @param objectJSONTemplate JSON-объект шаблона
         * @return Файл соответствуе(true)/не соответствует(false)
         */
        static bool isJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);

    private:

        /**
         * Класс используется для выброса исключения (при несовпадении JSON-структуры)
         */
        class JSONStructureNotMatch
        {};

        /**
         * Проверить JSON-структуру на соответствие шаблону (реализация)
         * @param objectJSON JSON-объект проверяемого
         * @param objectJSONTemplate JSON-объект шаблона
         * @return Файл соответствуе(true)/не соответствует(false)
         */
        static bool isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate);

    };

    /**
     * Класс реализует чтение и запись файлов с проверкой
     */
    class OperationFileAndJSON
    {

    public:

        OperationFileAndJSON() = delete;

        /**
         * Записать JSON-файл
         * @param filePath Путь JSON-файла
         * @param objectJSON JSON-объект для записи
         * @param formatByWidth Ширина отступа
         * @param callingFunction Ссылка на вызывающую функцию
         * @return Код ошибки
         */
        static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const int formatByWidth = 2,
                                       const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

        /**
         * Проверить JSON-структуру на соответствие шаблону
         * @param filePath Путь JSON-файла
         * @param objectJSON JSON-объект для записи
         * @param objectJSONTemplate JSON-объект шаблона
         * @param callingFunction Ссылка на вызывающую функцию
         * @return Код ошибки
         */
        static ErrorCode
        checkJSONStructureMatch(const std::string &filePath, const JSON &objectJSON, const JSON &objectJSONTemplate,
                                const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

/**
         * Проверить массив JSON-объекта на пустоту
         * @param objectJSON JSON-объект для записи
         * @param callingFunction Ссылка на вызывающую функцию
         * @return Код ошибки
         */
        static ErrorCode checkArray(const JSON &objectJSON,
                                             const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

        /**
         * Прочитать JSON-файл
         * @param filePath Путь JSON-файла
         * @param callingFunction Ссылка на вызывающую функцию
         * @return Пара JSON-объекта и кода ошибки
         */
        static std::pair<JSON, ErrorCode> readJSONFile(const std::string &filePath,
                                                       const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

        /**
         * Прочитать текстовый файл
         * @param filePath Путь JSON-файла
         * @param callingFunction Ссылка на вызывающую функцию
         * @return Пара текста и кода ошибки
         */
        static std::pair<std::string, ErrorCode> readTextFile(const std::string &filePath,
                                                              const boost::source_location &callingFunction = BOOST_CURRENT_LOCATION);

    };

}



#endif //SEARCH_ENGINE_OPERATIONFILEANDJSON_H
