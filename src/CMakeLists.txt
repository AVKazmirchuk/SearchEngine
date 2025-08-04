cmake_minimum_required(VERSION 3.21)

project(${Application_Name} VERSION 1.0.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../runtime")

message(STATUS "!!! src !!!")
message(STATUS "SE_INCLUDE_DIR2: ${SE_INCLUDE_DIR}")
message(STATUS "###${PROJECT_NAME}, ${CMAKE_PROJECT_NAME}")
add_executable(${Application_Name} main.cpp

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

target_include_directories(${Application_Name} PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(${Application_Name} PUBLIC ${SE_INCLUDE_DIR})

#target_include_directories(search_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(search_engine PRIVATE ${Boost_LIBRARIES})

#target_link_libraries(${Application_Name} PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(${Application_Name} PRIVATE kav_check::kav_check)
#target_link_libraries(${Application_Name} PRIVATE kav_logger::kav_logger)