//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_READTEXTFILE_H
#define SEARCH_ENGINE_READTEXTFILE_H


#include <source_location>
#include <string>
#include <vector>

#include "checkFile.h"

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
    static std::vector<std::string> readTextFile(const std::vector<std::string>& filePaths,
                                                 const std::string& message = "", ErrorLevel errorLevel = ErrorLevel::fatal,
                                                 const std::source_location &callingFunction = std::source_location::current());

};

#endif //SEARCH_ENGINE_READTEXTFILE_H
