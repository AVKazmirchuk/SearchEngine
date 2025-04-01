include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)



file(GLOB CPP_CONVERTER_JSON CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/converterJSON/*.cpp")
file(GLOB CPP_INVERTED_INDEX CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/invertedIndex/*.cpp")
file(GLOB CPP_RELEVANT_RESPONSE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/relevantResponse/*.cpp")
file(GLOB CPP_PREPARED_REQUEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/*.cpp")
file(GLOB CPP_CHECK_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/checkFile/*.cpp")
file(GLOB CPP_DOCUMENTS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/documents/*.cpp")
file(GLOB CPP_REQUESTS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/requests/*.cpp")
file(GLOB CPP_SEARCH_ENGINE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/searchEngine/*.cpp")
file(GLOB CPP_READ_WRITE_JSON_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/readWriteJSONFile/*.cpp")
file(GLOB CPP_READ_TEXT_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/readTextFile/*.cpp")
file(GLOB CPP_LOGGER CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/Logger/*.cpp")
file(GLOB CPP_GENERAL CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/general/*.cpp")

add_executable(search_engine_test testInvertedIndex.cpp testRelevantResponse.cpp test.cpp testCheckFile.cpp
        ${CPP_CONVERTER_JSON}
        ${CPP_INVERTED_INDEX}
        ${CPP_RELEVANT_RESPONSE}
        ${CPP_PREPARED_REQUEST}
        ${CPP_CHECK_FILE}
        ${CPP_DOCUMENTS}
        ${CPP_REQUESTS}
        ${CPP_SEARCH_ENGINE}
        ${CPP_READ_WRITE_JSON_FILE}
        ${CPP_READ_TEXT_FILE}
        ${CPP_LOGGER}
        ${CPP_GENERAL} testRelevantResponse.cpp testGeneral.cpp testCheckFilePathAndRequestsArrays.cpp testGeneral.h testCheckSetAnswers.cpp main.cpp)



target_include_directories(search_engine_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(search_engine_test PRIVATE nlohmann_json::nlohmann_json)



target_link_libraries(search_engine_test PRIVATE gtest_main)

include(GoogleTest)

gtest_discover_tests(search_engine_test)









