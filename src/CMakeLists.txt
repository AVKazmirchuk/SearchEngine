cmake_minimum_required(VERSION 3.21)

project(search_engine VERSION 1.0.0)

message(STATUS "!!! src !!!")
message(STATUS "SE_INCLUDE_DIR2: ${SE_INCLUDE_DIR}")
message(STATUS "###${PROJECT_NAME}, ${CMAKE_PROJECT_NAME}")
add_executable(search_engine src/main.cpp

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


        src/converterJSON/setAnswersJSON.cpp
        src/converterJSON/check.cpp
        src/converterJSON/misc.cpp

        src/dispatcherDetermineValidity/dispatcherDetermineValidity.cpp

        src/invertedIndex/updateInvertedIndexes.cpp
        src/invertedIndex/startInvertedIndexing.cpp
        src/invertedIndex/misc.cpp

        src/relevantResponse/updateRelevantResponses.cpp
        src/relevantResponse/countRelevanceOfResponses.cpp
        src/relevantResponse/evaluateRelativeRelevance.cpp

        src/relevantResponse/preparedRequest/misc.cpp
        src/relevantResponse/preparedRequest/updatePreparedRequests.cpp
        src/relevantResponse/preparedRequest/separateRequestsByWords.cpp
        src/relevantResponse/preparedRequest/sortWordsByFrequencyOfOccurrence.cpp
        src/relevantResponse/misc.cpp


        src/requests/updateRequests.cpp
        src/requests/misc.cpp

        src/searchEngine/searchModified.cpp
        src/searchEngine/exportRelevantResponses.cpp
        src/searchEngine/config.cpp

        src/readTextFile/readTextFile.cpp

        src/documents/documents.cpp

        src/general/general.cpp



        )

target_include_directories(search_engine PUBLIC ${SE_INCLUDE_DIR})
#target_include_directories(search_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(search_engine PRIVATE ${Boost_LIBRARIES})
#target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(search_engine PRIVATE kav_check::kav_check)
#arget_link_libraries(search_engine PRIVATE kav_logger::kav_logger)