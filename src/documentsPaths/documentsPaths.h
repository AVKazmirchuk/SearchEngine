//
// Created by Alexander on 15.02.2025.
//

#ifndef SEARCH_ENGINE_DOCUMENTSPATHS_H
#define SEARCH_ENGINE_DOCUMENTSPATHS_H



#include <string>
#include <vector>



/**
 * Класс реализует загрузку и хранение базы путей файлов документов
 */
class DocumentsPaths
{

public:

    DocumentsPaths() = default;

    /**
     * Обновить базу путей файлов документов
     * @param in_documents База путей файлов документов
     */
    void updateDocumentsPaths(const std::vector<std::string>& in_documentsPaths);

    /**
     * Обновить базу путей файлов документов
     * @param in_documents База путей файлов документов
     */
    void updateDocumentsPaths(std::vector<std::string>&& in_documentsPaths);

    /**
     * Получить ссылку на базу путей файлов документов
     * @return Ссылка на базу путей файлов документов
     */
    const std::vector<std::string>& getDocumentsPaths();

    /**
     * Очистить базу путей файлов документов
     */
    void clearDocumentsPaths();

private:

    /**
     * База путей файлов документов
     */
    std::vector<std::string> documentsPaths;

};



#endif //SEARCH_ENGINE_DOCUMENTSPATHS_H
