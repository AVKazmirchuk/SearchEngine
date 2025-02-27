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
    void updateDocuments(std::vector<std::string> in_documents);

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

    //ОСНОВНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * База документов
     */
    std::vector<std::string> documents;



    //ВСПОМОГАТЕЛЬНЫЕ ДАННЫЕ И ФУНКЦИИ

    /**
     * Преобразовать символ в нижний регистр
     * @param line Строка для преобразования
     * @return Преобразованная строка
     */
    std::string& characterToLower(std::string& line);

};



#endif //SEARCH_ENGINE_DOCUMENTS_H
