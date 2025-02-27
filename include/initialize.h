//
// Created by Alexander on 27.01.2025.
//

#ifndef SEARCH_ENGINE_INITIALIZE_H
#define SEARCH_ENGINE_INITIALIZE_H



#include "nlohmann/json.hpp"
#include <filesystem>
#include <fstream>



class Initialize
{
private:
    std::filesystem::path filePath;
    nlohmann::json objectJSON;

    //Вспомогательная функция проверки файла на неповреждённость JSON-структуры
    bool checkFileStructureValid();

    //Вспомогательная функция проверки файла на существование
    bool checkFileExists();

    //Вспомогательная функция проверки файла на пустоту
    bool checkFileEmpty();
public:
    Initialize(const std::string& in_filePath) : filePath{in_filePath}
    {};

    void openFile();

    std::string about();

};



#endif //SEARCH_ENGINE_INITIALIZE_H
