cmake_minimum_required(VERSION 3.21)

project(search_engine)

set(CMAKE_CXX_STANDARD 17)

set(SE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

add_subdirectory(nlohmann_json)

set(JSON_BuildTests OFF CACHE INTERNAL "")

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)



add_subdirectory(tests)




