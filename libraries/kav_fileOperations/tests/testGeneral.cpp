//
// Created by Alexander on 27.03.2025.
//


#include "testGeneral.h"



void putFiles()
{
    std::filesystem::remove("config.json");
    std::filesystem::remove("configNotValid.json");
    std::filesystem::remove("file001.txt");
    std::filesystem::remove("fileMultylines.txt");
    std::filesystem::remove("fileMultylines-2.txt");
    std::filesystem::remove("connectDisk.bat");
    std::filesystem::remove("disconnectDisk.bat");

    std::filesystem::copy("../../tests/resources/config.json", "config.json");
    std::filesystem::copy("../../tests/resources/configNotValid.json", "configNotValid.json");
    std::filesystem::copy("../../tests/resources/file001.txt", "file001.txt");
    std::filesystem::copy("../../tests/resources/fileMultylines.txt", "fileMultylines.txt");
    std::filesystem::copy("../../tests/resources/fileMultylines-2.txt", "fileMultylines-2.txt");
    std::filesystem::copy("../../tests/resources/connectDisk.bat", "connectDisk.bat");
    std::filesystem::copy("../../tests/resources/disconnectDisk.bat", "disconnectDisk.bat");
}

