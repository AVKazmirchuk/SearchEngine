cmake_minimum_required(VERSION 3.21)

add_executable(search_engine main.cpp

        ${SE_INCLUDE_DIR}/converterJSON.h
        ${SE_INCLUDE_DIR}/documents.h
        ${SE_INCLUDE_DIR}/entry.h

        ${SE_INCLUDE_DIR}/invertedIndex.h
        ${SE_INCLUDE_DIR}/relativeIndex.h
        ${SE_INCLUDE_DIR}/relevantResponse.h
        ${SE_INCLUDE_DIR}/requests.h
        ${SE_INCLUDE_DIR}/searchEngine.h
        ${SE_INCLUDE_DIR}/dispatcherDetermineValidity.h
        ${SE_INCLUDE_DIR}/types.h

        ${SE_INCLUDE_DIR}/readTextFile.h
        ${SE_INCLUDE_DIR}/general.h

        converterJSON/setAnswersJSON.cpp
        converterJSON/check.cpp
        converterJSON/misc.cpp

        dispatcherDetermineValidity/dispatcherDetermineValidity.cpp

        invertedIndex/updateInvertedIndexes.cpp
        invertedIndex/startInvertedIndexing.cpp
        invertedIndex/misc.cpp

        relevantResponse/updateRelevantResponses.cpp
        relevantResponse/countRelevanceOfResponses.cpp
        relevantResponse/evaluateRelativeRelevance.cpp

        relevantResponse/preparedRequest/misc.cpp
        relevantResponse/preparedRequest/updatePreparedRequests.cpp
        relevantResponse/preparedRequest/separateRequestsByWords.cpp
        relevantResponse/preparedRequest/sortWordsByFrequencyOfOccurrence.cpp
        relevantResponse/misc.cpp


        requests/updateRequests.cpp
        requests/misc.cpp

        searchEngine/searchModified.cpp
        searchEngine/exportRelevantResponses.cpp
        searchEngine/config.cpp

        readTextFile/readTextFile.cpp

        documents/documents.cpp

        general/general.cpp



        )

target_include_directories(search_engine PUBLIC ${SE_INCLUDE_DIR})