include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(search_engine_test testInvertedIndex.cpp test.cpp)

target_link_libraries(search_engine_test PRIVATE gtest_main)

target_include_directories(search_engine_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(search_engine_test PUBLIC ${SE_INCLUDE_DIR})

include(GoogleTest)

gtest_discover_tests(search_engine_test)









