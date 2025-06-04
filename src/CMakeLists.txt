cmake_minimum_required(VERSION 3.21)

add_executable(search_engine main.cpp

        ${SE_INCLUDE_DIR}/converterJSON.h
        ${SE_INCLUDE_DIR}/documents.h
        ${SE_INCLUDE_DIR}/entry.h
        ${SE_INCLUDE_DIR}/checkFileException.h
        ${SE_INCLUDE_DIR}/invertedIndex.h
        ${SE_INCLUDE_DIR}/relativeIndex.h
        ${SE_INCLUDE_DIR}/relevantResponse.h
        ${SE_INCLUDE_DIR}/requests.h
        ${SE_INCLUDE_DIR}/searchEngine.h
        ${SE_INCLUDE_DIR}/fileOperation.h
        ${SE_INCLUDE_DIR}/readTextFile.h
        ${SE_INCLUDE_DIR}/general.h
        ${SE_INCLUDE_DIR}/logger.h

        converterJSON/setAnswersJSON.cpp
        converterJSON/check.cpp

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


        requests/updateRequests.cpp

        searchEngine/searchModified.cpp
        searchEngine/exportRelevantResponses.cpp

        readTextFile/readTextFile.cpp

        checkFile/checkFile.cpp

        documents/documents.cpp

        general/general.cpp

        fileOperation/fileOperation.cpp

        relevantResponse/misc.cpp requests/misc.cpp converterJSON/misc.cpp Logger/logger.cpp monitorSender/monitorSender.cpp Logger/loging.cpp ../include/monitorSender.h ../include/termcolor.h Logger/identifyFile.cpp Logger/run.cpp Logger/setup.cpp Logger/config.cpp searchEngine/config.cpp)

target_include_directories(search_engine PUBLIC ${SE_INCLUDE_DIR})