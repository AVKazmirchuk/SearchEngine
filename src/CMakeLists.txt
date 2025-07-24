cmake_minimum_required(VERSION 3.21)

message(STATUS "SE_INCLUDE_DIR2 ${SE_INCLUDE_DIR}")

add_executable(search_engine main.cpp

        ../include/converterJSON.h
        ../include/documents.h
        ../include/entry.h

        ../include/invertedIndex.h
        ../include/relativeIndex.h
        ../include/relevantResponse.h
        ../include/requests.h
        ../include/searchEngine.h
        ../include/dispatcherDetermineValidity.h
        ../include/types.h

        ../include/readTextFile.h
        ../include/general.h
        #${SE_INCLUDE_DIR}/general.h

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
#target_include_directories(search_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(search_engine PRIVATE ${Boost_LIBRARIES} PRIVATE nlohmann_json::nlohmann_json PRIVATE kav_check::kav_check PRIVATE kav_logger::kav_logger)
