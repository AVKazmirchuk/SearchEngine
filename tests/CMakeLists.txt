include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)



FetchContent_MakeAvailable(googletest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

enable_testing()

add_executable(search_engine_test test.cpp testInvertedIndex.cpp)

target_link_libraries(search_engine_test PRIVATE gtest_main)

# Include directories (including where GoogleTest is built)
target_include_directories(search_engine_test PRIVATE ${gtest_SOURCE_DIR}/include)

# Add include directories for tests to find headers
target_include_directories(search_engine_test PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)

gtest_discover_tests(search_engine_test)









