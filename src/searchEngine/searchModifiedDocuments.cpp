//
// Created by Alexander on 19.02.2025.
//


#include "general.h"
#include "searchEngine.h"



void SearchEngine::searchModifiedDocuments()
{
    //Очистить список документов
    documentsObj.clearDocuments();

    //Обновить список документов из файлов
    documentsObj.updateDocuments(ReadTextFile::readTextFile(converterJSONObj.getFilePaths()));

    //Обновить базу инвертированного индекса
    invertedIndexObj.updateInvertedIndexes();

    //Рассчитать релевантность ответов
    relevantResponseObj.updateRelevantResponses();

    //Записать в файл answers.json результаты поиска, с учётом максимального количества ответов
    converterJSONObj.setAnswersJSON(exportRelevantResponses(), converterJSONObj.getMaxResponses());

    //Записать в JSON-файл результаты поиска
    ReadWriteJSONFile::writeJSONFile(converterJSONObj.getAnswersJSON(), constants::answersFilePath);
}