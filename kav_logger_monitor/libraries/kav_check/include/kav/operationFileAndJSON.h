//
// Created by Alexander on 25.02.2025.
//

#ifndef KAV_CHECK_OPERATIONFILEANDJSON_H
#define KAV_CHECK_OPERATIONFILEANDJSON_H



#include <fstream>
#include <string>
#include <thread>

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
         * @param objectJSON Ссылка на JSON-объект проверяемого
         * @param objectJSONTemplate Ссылка на JSON-объект шаблона
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
         * @param objectJSON Ссылка на JSON-объект проверяемого
         * @param objectJSONTemplate Ссылка на JSON-объект шаблона
         * @return Файл соответствуе(true)/не соответствует(false)
         */
        static bool isJSONStructureMatchImpl(const JSON &objectJSON, const JSON &objectJSONTemplate);

    };

    /**
     * Класс реализует чтение и запись файлов с проверкой, а также проверку JSON-объектов
     */
    class OperationFileAndJSON
    {

    public:

        OperationFileAndJSON() = delete;

        /**
         * Записать JSON-файл
         * @param filePath Ссылка на путь JSON-файла
         * @param objectJSON Ссылка на JSON-объект для записи
         * @param formatByWidth Ширина отступа
         * @return Код ошибки
         */
        static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const unsigned int formatByWidth = 2);

        /**
         * Проверить JSON-структуру на соответствие шаблону
         * @param objectJSON Ссылка на JSON-объект для проверки
         * @param objectJSONTemplate Ссылка на JSON-объект шаблона
         * @return Код ошибки
         */
        static ErrorCode checkJSONStructureMatch(const JSON &objectJSON, const JSON &objectJSONTemplate);

       /**
         * Проверить массив JSON-объекта на пустоту
         * @param objectJSON Ссылка на JSON-объект для проверки
         * @return Код ошибки
         */
        static ErrorCode checkArray(const JSON &objectJSON);

        /**
         * Прочитать JSON-файл
         * @param filePath Ссылка на путь JSON-файла
         * @return Пара JSON-объекта и кода ошибки
         */
        static std::pair<JSON, ErrorCode> readJSONFile(const std::string &filePath);

        /**
         * Прочитать текстовый файл
         * @param filePath Ссылка на путь текстового файла
         * @return Пара текста и кода ошибки
         */
        static std::pair<std::string, ErrorCode> readTextFile(const std::string &filePath);

        /**
         * Записать текстовый файл
         * @param filePath Ссылка на путь текстового файла
         * @param text Текст для записи
         * @param openModeFile Режим открытия файла
         * @return Код ошибки
         */
        static ErrorCode writeTextFile(const std::string &filePath, const std::string &text, std::ios_base::openmode openModeFile = std::ios::out);

        //Для тестирования передачи контейнера по ссылке
        //static void readTextFileRef(const std::string &filePath, std::string &document, ErrorCode &errorCode);
    };

}



#endif //KAV_CHECK_OPERATIONFILEANDJSON_H
