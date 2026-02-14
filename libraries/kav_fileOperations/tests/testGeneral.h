//
// Created by Alexander on 27.03.2025.
//



#ifndef SEARCH_ENGINE_TESTGENERAL_H
#define SEARCH_ENGINE_TESTGENERAL_H

#include "operationFileAndJSON.h"



/**
 * Класс хранения переменных программы
 */
class ProgramArguments
{

public:

    ProgramArguments() = delete;

    /**
     * Путь файла конфигурации
     * @return Ссылка на переменную
     */
    static const std::string& configFilePath()
    {
        //Значение по умолчанию
        static const std::string variable{"config.json"};
        return variable;
    }

    /**
     * Прочитать JSON-шаблон файла конфигурации
     * @return Ссылка на переменную
     */
    static const kav::JSON &configTemplate()
    {
        //Значение по умолчанию
        static const kav::JSON variable = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "1.0.0",
        "max_responses": 5
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
     ]
    }
    )");

        return variable;
    }

    /**
     * Прочитать несоответствующий структуре JSON-шаблон файла конфигурации
     * @return Ссылка на переменную
     */
    static const kav::JSON &configNotMatchTemplate()
    {
        //Значение по умолчанию
        static const kav::JSON variable = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1"
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
     ]
    }
    )");

        return variable;
    }

    /**
     * Прочитать несоответствующий структуре JSON-шаблон файла конфигурации (несовпадение типа)
     * @return Ссылка на переменную
     */
    static const kav::JSON &configNotMatchNotTypeTemplate()
    {
        //Значение по умолчанию
        static const kav::JSON variable = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 0.5
      },
     "files": [
       "resources/file001.txt",
       "resources/file002.txt",
       "resources/file003.txt"
     ]
    }
    )");

        return variable;
    }

    /**
     * Прочитать JSON-шаблон файла конфигурации с пустым массивом
     * @return Ссылка на переменную
     */
    static const kav::JSON &configArrayEmptyTemplate()
    {
        //Значение по умолчанию
        static const kav::JSON variable = kav::JSON::parse(R"(
    {
      "config": {
        "name": "SkillboxSearchEngine",
        "version": "0.1",
        "max_responses": 5
      },
     "files": [

     ]
    }
    )");

        return variable;
    }

    /**
     * Путь файла конфигурации с повреждённой структурой
     * @return Ссылка на переменную
     */
    static const std::string& configNotValid()
    {
        //Значение по умолчанию
        static const std::string variable{"configNotValid.json"};
        return variable;
    }

    /**
     * Путь текстового файла
     * @return Ссылка на переменную
     */
    static const std::string& textFile()
    {
        //Значение по умолчанию
        static const std::string variable{"file001.txt"};
        return variable;
    }

    /**
     * Путь текстового файла со строками
     * @return Ссылка на переменную
     */
    static const std::string& textFileMultylines()
    {
        //Значение по умолчанию
        static const std::string variable{"fileMultylines.txt"};
        return variable;
    }

    /**
     * Путь текстового файла со строками
     * @return Ссылка на переменную
     */
    static const std::string& textFileOneLine_withLineFeed()
    {
        //Значение по умолчанию
        static const std::string variable{"fileOneLine-withLineFeed.txt"};
        return variable;
    }

    /**
     * Путь текстового файла со строками
     * @return Ссылка на переменную
     */
    static const std::string& textFileOneLine_withoutLineFeed()
    {
        //Значение по умолчанию
        static const std::string variable{"fileOneLine-withoutLineFeed.txt"};
        return variable;
    }

    /**
     * Путь текстового файла для записи
     * @return Ссылка на переменную
     */
    static const std::string& textFileForWrite()
    {
        //Значение по умолчанию
        static const std::string variable{"textFileForWrite.txt"};
        return variable;
    }

    /**
     * Текстовая строка для записи
     * @return Ссылка на переменную
     */
    static const std::string& textString()
    {
        //Значение по умолчанию
        static const std::string variable{"It's just a text string!"};
        return variable;
    }

    /**
     * Содержимое файла file001.txt
     * @return Ссылка на переменную
     */
    static const std::string& fileContents()
    {
        //Значение по умолчанию
        static const std::string variable{"modern american movies of the past    years have introduced to the audiences a fresh generation of actors  kevin spacey  russell crowe  brad pitt  john cusack  matt damon  edward norton  frances mcdormand  gwyneth paltrow and julianne moore have given performances as vivid as their illustrious predecessors  unlike the iconic stars of hollywood s classic era  who always seemed to be playing themselves   stars like cary grant  john wayne  gary cooper  clark gable  elizabeth taylor   the current generation of american actors disappear into their roles  playing parts that differ from one movie to the next  most of their movies are financed by hollywood  they are a promise to the variety of american filmmaking on important reason for this eclecticism is the impact of smaller  semi independent studios  studios like sony pictures classics and dream works specialize in producing or distributing avant garde movies   however  no studio head has been more influential or more successful in promoting innovative american  as well as foreign language films  than harvey weinstein of miramax  in many ways  weinstein is the crucial link between the movies of the     s and those of the past    years  when weinstein launched miramax in       he wanted to produce the sort of challenging films he had adored in his youth  this is precisely what he has done  miramax has been responsible for bringing to the united states foreign films like the crying game  cinema paradiso  ii postino  life is beautiful  and like water for chocolate  all of these films made money  despite the stereotype abroad that americans will only pay to see blockbuster movies made in hollywood   still  no matter how important the contributions and convictions of particular producers  directors or actors have been  what contemporary american movies have most in common with the films of the     s and     s  is a seriousness of artistic purpose combined with a desire to enthrall the audience  these twin ambitions are  by no means  uniquely american  wherever they have come from  the greatest directors   charlie chaplin  orson welles  alfred hitchcock  john ford  howard hawks  federico fellini  francis ford coppola  martin scorsese  steven spielberg   they have always recognized the intimate relationship between entertainment and art   to sum it up american films of the new generation are more open to their audience feelings  emotions  the inside world  thoughts and actions  people of the new american generation have a great opportunity to watch what is going on inside them in the movies shot outside"};
        return variable;
    }

    /**
     * Содержимое файла fileMultylines.txt (первая строка)
     * @return Ссылка на переменную
     */
    static const std::string& fileFirstLineContents()
    {
        //Значение по умолчанию
        static const std::string variable{"   modern american movies of the past    years have introduced to the audiences a fresh generation of actors  kevin spacey  russell crowe  brad pitt  john cusack  matt damon  edward norton   "};
        return variable;
    }

    /**
     * Содержимое файла fileMultylines.txt (последняя строка)
     * @return Ссылка на переменную
     */
    static const std::string& fileLastLineContents()
    {
        //Значение по умолчанию
        static const std::string variable{"actions  people of the new american generation have a great opportunity to watch what is going on inside them in the movies shot outside"};
        return variable;
    }

    /**
     * Содержимое файла fileMultylines_2.txt (последняя строка)
     * @return Ссылка на переменную
     */
    static const std::string& fileLastLineContents_2()
    {
        //Значение по умолчанию
        static const std::string variable{"actions  people of the new american generation have a great opportunity to watch what is going on inside them in the movies shot outside"};
        return variable;
    }

    /**
     * Имя поля массива
     * @return Ссылка на переменную
     */
    static const std::string& files()
    {
        //Значение по умолчанию
        static const std::string variable{"files"};
        return variable;
    }

};



/*
 * Записать файлы для тестирования
 */
void putFiles();



#endif //SEARCH_ENGINE_TESTGENERAL_H
