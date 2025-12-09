//
// Created by Alexander on 15.02.2025.
//

#ifndef SEARCH_ENGINE_DOCUMENTS_H
#define SEARCH_ENGINE_DOCUMENTS_H



#include <string>
#include <vector>



/**
 * Класс реализует загрузку и хранение базы документов
 */
class Documents
{

public:

    Documents() = default;

    /**
     * Обновить базу документов
     * @param in_documents База документов
     */
    void updateDocuments(const std::vector<std::string>& in_documents);

    /**
     * Обновить базу документов
     * @param in_documents База документов
     */
    void updateDocuments(std::vector<std::string>&& in_documents);

    /**
     * Получить ссылку на базу документов
     * @return Ссылка на базу документов
     */
    const std::vector<std::string>& getDocuments();

    /**
     * Очистить базу документов
     */
    void clearDocuments();

private:

    /**
     * База документов
     */
    std::vector<std::string> documents;

};



#endif //SEARCH_ENGINE_DOCUMENTS_H
