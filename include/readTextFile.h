//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_READTEXTFILE_H
#define SEARCH_ENGINE_READTEXTFILE_H



#include <string>
#include <vector>


/**
 * Класс реализует чтение текстовых файлов
 */
class ReadTextFile
{

public:

    /**
     *
     */
    ReadTextFile() = default;

    /**
     * Прочитать документы в отдельных потоках
     * @param filePaths Список путей документов
     * @return Документы
     */
    static std::vector<std::string> readTextFile(const std::vector<std::string>& filePaths);

};

#endif //SEARCH_ENGINE_READTEXTFILE_H
