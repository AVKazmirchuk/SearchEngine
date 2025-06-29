cmake_minimum_required(VERSION 3.21)

project(search_engine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../runtime")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

set(SE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)



set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
set(Boost_LIBRARY_DIR "C:\\boost_1_87_0\\stage\\lib")

find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})



add_subdirectory(src)

#if (NOT TARGET nlohmann_json)

#    add_subdirectory(nlohmann_json)
#    set(JSON_BuildTests OFF CACHE INTERNAL "")
#    target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)

#endif()

set(nlohmann_json_DIR "C:\\nlohmann_json\\cmake")
find_package(nlohmann_json 3.12.0 REQUIRED)
set(JSON_BuildTests OFF CACHE INTERNAL "")
target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)


add_subdirectory(tests)


add_subdirectory(kav_check)


target_link_libraries(search_engine PRIVATE kav_check)

add_subdirectory(monitor)

target_link_libraries(search_engine ${Boost_LIBRARIES})