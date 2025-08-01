# Установить минимальную версию cmake
cmake_minimum_required(VERSION 3.21)#

# Задать имя для проекта, версию, название языка
project(search_engine_monitor VERSION 1.0.0 LANGUAGES CXX)#

function(add_subdirectory _dir)
    get_filename_component(_fullpath ${_dir} REALPATH)
    if (EXISTS ${_fullpath} AND EXISTS ${_fullpath}/CMakeLists.txt)
        get_property(_included_dirs GLOBAL PROPERTY GlobalAddSubdirectoryOnceIncluded)
        list(FIND _included_dirs "${_fullpath}" _used_index)
        if (${_used_index} EQUAL -1)
            set_property(GLOBAL APPEND PROPERTY GlobalAddSubdirectoryOnceIncluded "${_fullpath}")
            _add_subdirectory(${_dir} ${ARGN})
        endif()
    else()
        message(WARNING "add_subdirectory: Can't find ${_fullpath}/CMakeLists.txt")
    endif()
endfunction(add_subdirectory _dir)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../runtime")

add_executable(search_engine_monitor main.cpp  monitorReceiver.h monitorReceiver.cpp termcolor.h monitor.cpp monitor.h general.h general.cpp)

set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
set(Boost_LIBRARY_DIR "C:\\boost_1_87_0\\stage\\lib")

find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

find_package(nlohmann_json REQUIRED)
set(JSON_BuildTests OFF CACHE INTERNAL "")
target_link_libraries(search_engine_monitor PRIVATE nlohmann_json::nlohmann_json)

#if (NOT TARGET kav_check)
add_subdirectory(kav_check)
#find_package(kav_check REQUIRED)
target_link_libraries(search_engine_monitor PRIVATE kav_check::kav_check)
#endif()

#target_link_libraries(search_engine_monitor ${Boost_LIBRARIES})


#target_link_libraries(search_engine_monitor PRIVATE nlohmann_json::nlohmann_json)

