//
// Created by Alexander on 15.02.2025.
//

#ifndef SEARCH_ENGINE_DOCUMENTS_H
#define SEARCH_ENGINE_DOCUMENTS_H



#include <string>
#include <vector>



/**
 * Класс реализует загрузку и хранение базы документов или путей файлов документов
 */
class Documents
{

public:

    Documents() = default;

    /**
     * Обновить базу документов или путей файлов документов
     * @param in_documents База документов или путей файлов документов
     */
    void updateDocuments(const std::vector<std::string>& in_documents);

    /**
     * Обновить базу документов или путей файлов документов
     * @param in_documents База документов или путей файлов документов
     */
    void updateDocuments(std::vector<std::string>&& in_documents);

    /**
     * Получить ссылку на базу документов или путей файлов документов
     * @return Ссылка на базу документов или путей файлов документов
     */
    const std::vector<std::string>& getDocuments();

    /**
     * Очистить базу документов или путей файлов документов
     */
    void clearDocuments();

private:

    /**
     * База документов или путей файлов документов
     */
    std::vector<std::string> documents;

};



#endif //SEARCH_ENGINE_DOCUMENTS_H
