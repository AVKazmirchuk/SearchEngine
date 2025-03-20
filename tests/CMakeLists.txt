include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(src)

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)



add_executable(search_engine_test testInvertedIndex.cpp test.cpp

        ${PROJECT_SOURCE_DIR}/src/converterJSON/getFilePaths.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/getMaxResponses.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/getRequests.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/setAnswersJSON.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/getAnswersJSON.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/convertIdtoStr.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/accumulateRank.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/about.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/checkFilePath.cpp
        ${PROJECT_SOURCE_DIR}/src/converterJSON/checkRequests.cpp

        ${PROJECT_SOURCE_DIR}/src/invertedIndex/updateInvertedIndexes.cpp
        ${PROJECT_SOURCE_DIR}/src/invertedIndex/getInvertedIndexes.cpp
        ${PROJECT_SOURCE_DIR}/src/invertedIndex/clearInvertedIndexes.cpp
        ${PROJECT_SOURCE_DIR}/src/invertedIndex/addWord.cpp
        ${PROJECT_SOURCE_DIR}/src/invertedIndex/defineWord.cpp
        ${PROJECT_SOURCE_DIR}/src/invertedIndex/startInvertedIndexing.cpp

        ${PROJECT_SOURCE_DIR}/src/relevantResponse/updateRelevantResponses.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/getRelevantResponses.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/countRelevanceOfResponses.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/evaluateRelativeRelevance.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/sortByDescendingRelevance.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/clearRelevantResponses.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/discoverNumberOfDocuments.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/getInvertedIndexStructures.cpp

        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/clearPreparedRequests.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/getPreparedRequests.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/updatePreparedRequests.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/separateRequestsByWords.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/getInvertedIndexStructures.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/sortWordsByFrequencyOfOccurrence.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/convertPreparedRequestsToUniqueWords.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/getFrequencyOfOccurrence.cpp
        ${PROJECT_SOURCE_DIR}/src/relevantResponse/roundUpToPrecision.cpp


        ${PROJECT_SOURCE_DIR}/src/checkFile/isJSONStructureValid.cpp
        ${PROJECT_SOURCE_DIR}/src/checkFile/isExist.cpp
        ${PROJECT_SOURCE_DIR}/src/checkFile/isEmpty.cpp
        ${PROJECT_SOURCE_DIR}/src/checkFile/isJSONStructureMatch.cpp
        ${PROJECT_SOURCE_DIR}/src/checkFile/isJSONStructureMatchImpl.cpp

        ${PROJECT_SOURCE_DIR}/src/documents/updateDocuments.cpp
        ${PROJECT_SOURCE_DIR}/src/documents/getDocuments.cpp
        ${PROJECT_SOURCE_DIR}/src/documents/clearDocuments.cpp

        ${PROJECT_SOURCE_DIR}/src/requests/updateRequests.cpp
        ${PROJECT_SOURCE_DIR}/src/requests/getRequests.cpp
        ${PROJECT_SOURCE_DIR}/src/requests/clearRequests.cpp

        ${PROJECT_SOURCE_DIR}/src/searchEngine/searchModifiedAll.cpp
        ${PROJECT_SOURCE_DIR}/src/searchEngine/exportRelevantResponses.cpp
        ${PROJECT_SOURCE_DIR}/src/searchEngine/searchModifiedDocuments.cpp
        ${PROJECT_SOURCE_DIR}/src/searchEngine/searchModifiedRequests.cpp

        ${PROJECT_SOURCE_DIR}/src/readWriteJSONFile/writeJSONFile.cpp
        ${PROJECT_SOURCE_DIR}/src/readWriteJSONFile/readJSONFile.cpp

        ${PROJECT_SOURCE_DIR}/src/readTextFile/readTextFile.cpp

        ${PROJECT_SOURCE_DIR}/src/constants.cpp
        ${PROJECT_SOURCE_DIR}/src/exitProgram.cpp

        ${PROJECT_SOURCE_DIR}/src/Logger/info.cpp
        ${PROJECT_SOURCE_DIR}/src/Logger/warn.cpp
        ${PROJECT_SOURCE_DIR}/src/Logger/error.cpp
        ${PROJECT_SOURCE_DIR}/src/Logger/fatal.cpp)

target_link_libraries(search_engine_test PRIVATE gtest_main)


#target_include_directories(search_engine_test PRIVATE ${gtest_SOURCE_DIR}/include)



target_include_directories(search_engine_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
#target_include_directories(search_engine_test PRIVATE ${PROJECT_SOURCE_DIR}/src)

target_link_libraries(search_engine_test PRIVATE nlohmann_json::nlohmann_json)

#target_include_directories(someprojectname "${CMAKE_CURRENT_SOURCE_DIR}/src")



include(GoogleTest)

gtest_discover_tests(search_engine_test)









