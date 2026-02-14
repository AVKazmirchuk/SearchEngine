//
// Created by Alexander on 25.02.2025.
//

#ifndef kav_fileOperations_OPERATIONFILEANDJSON_H
#define kav_fileOperations_OPERATIONFILEANDJSON_H



/*
 * Для прохождения тестов на запись-чтение файлов (в процессе) для эмуляции ошибки используется сетевой диск. При записи-чтении
 * диск отключается. Перед запуском тестов надо расшарить директорию (не которую использует IDE по умолчанию) с правами на запись,
 * положить файлы config.json, file001.txt, fileMultylines.txt, и поправить файлы: connectDisk.bat,
 * disconnectDisk.bat. Раскомментировать макрос KAV_ENABLE_ERROR_CHECKING_DURING_THE_OPERATION. Есть вариант использовать для
 * этого Windows API, но там всё не так просто. Другого автоматического способа не нашёл для эмуляции ошибки. Пока хоть что-то.
 * Поэтому эти функции проверки отключены.
 */

//#define KAV_ENABLE_ERROR_CHECKING_DURING_THE_OPERATION

#ifdef KAV_ENABLE_ERROR_CHECKING_DURING_THE_OPERATION
    #define KAV_SYSTEM_DISCONNECT_DISK system("disconnectDisk.bat");
    #define KAV_SYSTEM_CONNECT_DISK system("connectDisk.bat");
#else
    #define KAV_SYSTEM_DISCONNECT_DISK //system("disconnectDisk.bat");
    #define KAV_SYSTEM_CONNECT_DISK //system("connectDisk.bat");
#endif


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
        static ErrorCode writeJSONFile(const std::string &filePath, const JSON &objectJSON, const int formatByWidth = 2);

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
         * Прочитать последнюю строку текстового файла
         * @param filePath Ссылка на путь текстового файла
         * @return Пара строки и кода ошибки
         */
        static std::pair<std::string, ErrorCode> readLastLineFromTextFile(const std::string &filePath);

        /**
         * Прочитать первую строку текстового файла
         * @param filePath Ссылка на путь текстового файла
         * @return Пара строки и кода ошибки
         */
        static std::pair<std::string, ErrorCode> readFirstLineFromTextFile(const std::string &filePath);

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



#endif //kav_fileOperations_OPERATIONFILEANDJSON_H
