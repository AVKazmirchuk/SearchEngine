cmake_minimum_required(VERSION 3.21)

add_executable(search_engine main.cpp

        ${SE_INCLUDE_DIR}/converterJSON.h
        ${SE_INCLUDE_DIR}/documents.h
        ${SE_INCLUDE_DIR}/entry.h
        ${SE_INCLUDE_DIR}/exceptions.h
        ${SE_INCLUDE_DIR}/initialize.h
        ${SE_INCLUDE_DIR}/invertedIndex.h
        ${SE_INCLUDE_DIR}/relativeIndex.h
        ${SE_INCLUDE_DIR}/relevantResponse.h
        ${SE_INCLUDE_DIR}/requests.h
        ${SE_INCLUDE_DIR}/searchEngine.h
        ${SE_INCLUDE_DIR}/readWriteJSONFile.h
        ${SE_INCLUDE_DIR}/readWriteTextFile.h
        ${SE_INCLUDE_DIR}/general.h

        ${SE_INCLUDE_DIR}/parallelization.h

        converterJSON/getFilePaths.cpp
        converterJSON/getMaxResponses.cpp
        converterJSON/getRequests.cpp
        converterJSON/putAnswers.cpp

        invertedIndex/updateInvertedIndexes.cpp
        invertedIndex/getInvertedIndexes.cpp
        invertedIndex/clearInvertedIndexes.cpp
        invertedIndex/addWord.cpp
        invertedIndex/defineWord.cpp
        invertedIndex/startThreads.cpp

        relevantResponse/updateRelevantResponses.cpp
        relevantResponse/getRelevantResponses.cpp
        relevantResponse/countRelevanceOfResponses.cpp
        relevantResponse/evaluateRelativeRelevance.cpp
        relevantResponse/sortByDescendingRelevance.cpp
        relevantResponse/clearRelevantResponses.cpp
        relevantResponse/discoverNumberOfDocuments.cpp
        relevantResponse/getInvertedIndexStructures.cpp

        relevantResponse/preparedRequest/clearPreparedRequests.cpp
        relevantResponse/preparedRequest/getPreparedRequests.cpp
        relevantResponse/preparedRequest/updatePreparedRequests.cpp
        relevantResponse/preparedRequest/separateRequestsByWords.cpp
        relevantResponse/preparedRequest/getInvertedIndexStructures.cpp
        relevantResponse/preparedRequest/sortWordsByFrequencyOfOccurrence.cpp
        relevantResponse/preparedRequest/convertPreparedRequestsToUniqueWords.cpp
        relevantResponse/preparedRequest/getFrequencyOfOccurrence.cpp
        relevantResponse/roundUpToPrecision.cpp


        initial/checkFileStructureValid.cpp
        initial/checkFileExists.cpp
        initial/initialize.cpp
        initial/checkFileEmpty.cpp

        documents/characterToLower.cpp
        documents/updateDocuments.cpp
        documents/getDocuments.cpp
        documents/clearDocuments.cpp

        requests/updateRequests.cpp
        requests/getRequests.cpp
        requests/characterToLower.cpp
        requests/clearRequests.cpp

        searchEngine/searchModifiedAll.cpp
        searchEngine/exportRelevantResponses.cpp
        searchEngine/searchModifiedDocuments.cpp
        searchEngine/searchModifiedRequests.cpp

        readWriteJSONFile/writeJSONFile.cpp
        readWriteJSONFile/readJSONFile.cpp

        readWriteTextFile/readTextFile.cpp

        constants.cpp
        exitProgram.cpp



        parallelization/startThreads.cpp converterJSON/getAnswersJSON.cpp converterJSON/convertIdtoStr.cpp converterJSON/accumulateRank.cpp)

target_include_directories(search_engine PUBLIC ${SE_INCLUDE_DIR})