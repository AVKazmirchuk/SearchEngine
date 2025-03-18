cmake_minimum_required(VERSION 3.21)

project(search_engine)

set(CMAKE_CXX_STANDARD 17)

set(SE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(tests)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)





#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
#)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
enable_testing()

#target_link_libraries(search_engine PRIVATE gtest_main)
#include(GoogleTest)
#gtest_discover_tests(search_engine)



#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

#set(gtest_disable_pthreads on)

#include(CTest)