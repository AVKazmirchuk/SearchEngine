//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H



#include <fstream>
#include <future>
#include <string>
#include <vector>
#include <utility>
#include <list>

#include <thread>
#include <mutex>


#include "nlohmann/json.hpp"

#include "DispatcherOperations.h"
#include "types.h"



/**
 * Класс реализует работу с JSON-объектами
 */
class ConverterJSON
{

public:

    /**
     * Инициализирует: ссылку на JSON-объект конфигурации, ссылку на JSON-объект запросов
     * @param in_configFilePath Ссылка на путь файла конфигурации
     * @param in_requestsFilePath Ссылка на путь файла запросов
     * @param in_precision Количество знаков после запятой
     */
    ConverterJSON(const std::string& in_configFilePath, const std::string& in_requestsFilePath, unsigned int in_precision)

    : configConverterJson(in_configFilePath, in_requestsFilePath),
    configJSON(configConverterJson.getConfigJSON()), requestsJSON(configConverterJson.getRequestsJSON()), precision{in_precision}

    {
        initialize();
    }

    /**
     * Инициализирует: ссылку на JSON-объект конфигурации, ссылку на JSON-объект запросов
     * @param in_configFilePath Ссылка на путь файла конфигурации
     * @param in_requestsFilePath Ссылка на путь файла запросов
     * @param in_precision Количество знаков после запятой
     */
    ConverterJSON(std::string&& in_configFilePath, std::string&& in_requestsFilePath, unsigned int in_precision)

            : configConverterJson(std::move(in_configFilePath), std::move(in_requestsFilePath)),
            configJSON(configConverterJson.getConfigJSON()), requestsJSON(configConverterJson.getRequestsJSON()), precision{in_precision}

    {
        initialize();
    }

    /**
     * О программе
     * @return Строка о программе (название, версия)
     */
    std::string about();

    /**
     * Получить список путей файлов документов
     * @return Список путей файлов документов
     */
    std::vector<std::string> getFilePaths();

    /**
     * Получить запросы
     * @return Запросы
     */
    std::vector<std::string> getRequests();

    /**
     * Получить значение максимального количества ответов
     * @return Значение максимального количества ответов
     */
    unsigned int getMaxResponses();

    /**
     * Записать в JSON-объект результаты поиска
     * @param answers Релевантность ответов
     */
    void setAnswersJSON(const std::vector<std::vector<std::pair<std::uint64_t , float>>>& answers);

    /**
     * Получить ссылку на JSON-объект ответов
     * @return Ссылка на JSON-объект ответов
     */
    JSON& getAnswersJSON();

private:

    /**
     * Класс реализует чтение и хранение параметров для настройки класса ConverterJSON
     */
    class ConfigConverterJSON
    {

    public:

        /**
         * Инициализирует класс
         * @param in_configFilePath Ссылка на путь файла конфигурации
         * @param in_requestsFilePath Ссылка на путь файла запросов
         */
        ConfigConverterJSON(const std::string& in_configFilePath, const std::string& in_requestsFilePath)
                : configFilePath{in_configFilePath}, requestsFilePath{in_requestsFilePath}
        {
            initialize();
        }

        /**
         * Инициализирует класс
         * @param in_configFilePath Ссылка на путь файла конфигурации
         * @param in_requestsFilePath Ссылка на путь файла запросов
         */
        ConfigConverterJSON(std::string&& in_configFilePath, std::string&& in_requestsFilePath)
                : configFilePath{std::move(in_configFilePath)}, requestsFilePath{std::move(in_requestsFilePath)}
        {
            initialize();
        }

        /**
         * Получить ссылку на JSON-объект конфигурации
         * @return JSON-объект конфигурации
         */
        [[nodiscard]] const JSON& getConfigJSON() const {return configJSON;}

        /**
         * Получить ссылку на JSON-объект запросов
         * @return JSON-объект запросов
         */
        [[nodiscard]] const JSON& getRequestsJSON() const {return requestsJSON;}

    private:

        //Шаблон JSON-объекта конфигурации
        const JSON configTemplate = JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
     ]
    }
    )");

        //Шаблон JSON-объекта запросов
        const JSON requestsTemplate = JSON::parse(R"(
    {
      "requests": [
        "of the and water is year",
        "water another good see",
        "music"
      ]
    }
    )");

        //Путь файла конфигурации
        std::string configFilePath;
        //Путь файла запросов
        std::string requestsFilePath;
        //JSON-объект конфигурации
        JSON configJSON;
        //JSON-объект запросов
        JSON requestsJSON;

        /**
         * Инициализировать (настроить) класс
         */
        void initialize();

    };

    //Класс хранит переменные названий полей файлов конфигурации, запросов, ответов
    class FileFieldNames
    {

    public:

        FileFieldNames() = delete;

        /**
         * Прочитать имя поля "config" файла конфигурации
         * @return Ссылка на переменную
         */
        static const std::string& configStr()
        {
            //Значение по умолчанию
            static const std::string variable{"config"};
            return variable;
        }

        /**
         * Прочитать имя поля "name" файла конфигурации
         * @return Ссылка на переменную
         */
        static const std::string& nameStr()
        {
            //Значение по умолчанию
            static const std::string variable{"name"};
            return variable;
        }

        /**
         * Прочитать имя поля "version" файла конфигурации
         * @return Ссылка на переменную
         */
        static const std::string& versionStr()
        {
            //Значение по умолчанию
            static const std::string variable{"version"};
            return variable;
        }

        /**
         * Прочитать имя поля "max_responses" файла конфигурации
         * @return Ссылка на переменную
         */
        static const std::string& max_responsesStr()
        {
            //Значение по умолчанию
            static const std::string variable{"max_responses"};
            return variable;
        }

        /**
         * Прочитать имя поля "files" файла конфигурации
         * @return Ссылка на переменную
         */
        static const std::string& filesStr()
        {
            //Значение по умолчанию
            static const std::string variable{"files"};
            return variable;
        }

        /**
         * Прочитать имя поля "requests" файла запросов
         * @return Ссылка на переменную
         */
        static const std::string& requestsStr()
        {
            //Значение по умолчанию
            static const std::string variable{"requests"};
            return variable;
        }

        /**
         * Прочитать имя поля "answers" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& answersStr()
        {
            //Значение по умолчанию
            static const std::string variable{"answers"};
            return variable;
        }

        /**
         * Прочитать имя поля "request" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& requestStr()
        {
            //Значение по умолчанию
            static const std::string variable{"request"};
            return variable;
        }

        /**
         * Прочитать имя поля "result" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& resultStr()
        {
            //Значение по умолчанию
            static const std::string variable{"result"};
            return variable;
        }

        /**
         * Прочитать значение "true" поля "result" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& trueStr()
        {
            //Значение по умолчанию
            static const std::string variable{"true"};
            return variable;
        }

        /**
         * Прочитать значение "false" поля "result" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& falseStr()
        {
            //Значение по умолчанию
            static const std::string variable{"false"};
            return variable;
        }

        /**
         * Прочитать имя поля "relevance" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& relevanceStr()
        {
            //Значение по умолчанию
            static const std::string variable{"relevance"};
            return variable;
        }

        /**
         * Прочитать имя поля "docid" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& docIdStr()
        {
            //Значение по умолчанию
            static const std::string variable{"docid"};
            return variable;
        }

        /**
         * Прочитать имя поля "rank" файла ответов
         * @return Ссылка на переменную
         */
        static const std::string& rankStr()
        {
            //Значение по умолчанию
            static const std::string variable{"rank"};
            return variable;
        }

    };//Класс хранит переменные названий полей файлов конфигурации, запросов, ответов*/



    //ОСНОВНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Объект чтения и хранения параметров для настройки класса ConverterJSON
     */
    ConfigConverterJSON configConverterJson;

    /**
     * Ссылка на JSON-объект конфигурации
     */
    const JSON& configJSON;

    /**
     * Ссылка на JSON-объект запросов
     */
    const JSON& requestsJSON;

    /**
     * JSON-объект ответов
     */
    JSON answersJSON;

    /**
     * Максимальное количество ответов
     */
    unsigned int maxResponses;

    //Инициализировать
    void initialize();



    //ВСПОМОГАТЕЛЬНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Количество знаков после запятой
     */
    const unsigned int precision;

    /**
     * Проверить пути файлов документов (существование)
     */
    void checkFilePath();

    /**
     * Проверить запросы (существование)
     */
    void checkRequests();

    /**
     * Определить суммарный ранг
     * @param answers Ответы
     * @param requestId ID запроса
     * @return Суммарный ранг
     */
    float accumulateRank(const std::vector<std::vector<std::pair<std::uint64_t, float>>>& answers, std::size_t requestId);

    /**
     * Преобразовать Id запроса в строку
     * @param requestId ID запроса
     * @param str Начальная строка
     * @return Преобразованная строка
     */
    std::string convertIdtoStr(std::size_t requestId, std::string str);

};



#endif //SEARCH_ENGINE_CONVERTERJSON_H
