//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_INITIALIZATION_H
#define SEARCH_ENGINE_INITIALIZATION_H



#include <filesystem>
#include <fstream>

#include "nlohmann/json.hpp"

#include "general.h"



class Initialization
{

public:

    Initialization(const std::string& in_configFilePath) : configFilePath{in_configFilePath}
    {};

    void openFile();

    std::string about();

private:

    std::filesystem::path configFilePath;
    nlohmann::json objectJSON;

    /**
     * Проверить файла на неповреждённость JSON-структуры
     * @return
     */
    bool checkJSONStructureValid();

    //Вспомогательная функция проверки файла на существование
    bool checkFileExists();

    //Вспомогательная функция проверки файла на пустоту
    bool checkFileEmpty();

};



#endif //SEARCH_ENGINE_INITIALIZATION_H
