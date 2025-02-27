//
// Created by Alexander on 25.02.2025.
//

#ifndef SEARCH_ENGINE_READWRITETEXTFILE_H
#define SEARCH_ENGINE_READWRITETEXTFILE_H



#include <string>
#include <vector>


/**
 * Класс реализует чтение и запись текстовых файлов
 */
class ReadWriteTextFile
{

public:

    /**
     *
     */
    ReadWriteTextFile() = default;

    /**
     * Прочитать документ
     * @param filePath Путь документа
     * @return Документ
     */
    std::string readTextFile(const std::string& filePath);

    /**
     * Прочитать документы в отдельных потоках
     * @param filePaths Список путей документов
     * @return Документы
     */
    std::vector<std::string> readTextFile(const std::vector<std::string>& filePaths);

};

#endif //SEARCH_ENGINE_READWRITETEXTFILE_H
