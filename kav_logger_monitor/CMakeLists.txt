# Установить минимальную версию cmake
cmake_minimum_required(VERSION 3.21)

# Задать имя для проекта, версию, название языка
project(logger_monitor VERSION 1.0.0 LANGUAGES CXX)

# TODO Непонятно работает (нестабильно в разных по-вложенности CMakeLists), можно поразбираться
#function(add_subdirectory _dir)
#    get_filename_component(_fullpath ${_dir} REALPATH)
#    if (EXISTS ${_fullpath} AND EXISTS ${_fullpath}/CMakeLists.txt)
#        get_property(_included_dirs GLOBAL PROPERTY GlobalAddSubdirectoryOnceIncluded)
#        list(FIND _included_dirs "${_fullpath}" _used_index)
#        if (${_used_index} EQUAL -1)
#            set_property(GLOBAL APPEND PROPERTY GlobalAddSubdirectoryOnceIncluded "${_fullpath}")
#            _add_subdirectory(${_dir} ${ARGN})
#        endif()
#    else()
#        message(WARNING "add_subdirectory: Can't find ${_fullpath}/CMakeLists.txt")
#    endif()
#    message(STATUS "kav_logger: path _dir: ${_fullpath}/CMakeLists.txt")
#endfunction(add_subdirectory _dir)

# Установить стандарт C++
set(CMAKE_CXX_STANDARD 20)
# Установить требование стандарта С++
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Отключить расширения компилятора
set(CMAKE_CXX_EXTENSIONS OFF)

# Поместить все целевые файлы RUNTIME при сборке
set(Runtime_Output_Directory "../../../runtime")
# Установить языковые флаги при сборке для всех конфигураций. Эти флаги будут передаваться при всех вызовах компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

# Задать имя приложения
set(Application_Name "logger_monitor")
# Задать переменную списка директорий с заголовками
set(Include_Directories "")
# Добавить директории с заголовками
LIST(APPEND Include_Directories ${CMAKE_SOURCE_DIR}/include)
LIST(APPEND Include_Directories ${CMAKE_SOURCE_DIR}/src)

# В зависимости от добавления библиотеки в проект, закомментировать-раскомментировать if-endif и find_package
#find_package(nlohmann_json REQUIRED)
if (NOT TARGET nlohmann_json)
    add_subdirectory(nlohmann_json)
endif()
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install ON CACHE INTERNAL "")

set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
find_package(Boost REQUIRED)

# В зависимости от добавления библиотеки в проект, закомментировать-раскомментировать if-endif и find_package
#find_package(kav_check REQUIRED)
if (NOT TARGET kav_check)
    add_subdirectory(kav_check)
endif()
set(check_Install ON CACHE INTERNAL "")

add_subdirectory(src)

# Указать библиотеки, которые нужно использовать при компоновке заданной цели и/или её зависимостей
target_link_libraries(${Application_Name} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${Application_Name} PRIVATE kav_check::kav_check)
