# Установить минимальную версию cmake
cmake_minimum_required(VERSION 3.21)

# Задать имя для проекта, версию, название языка
project(search_engine-solution VERSION 1.0.0  LANGUAGES CXX)

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
set(Runtime_Output_Directory "../../runtime")
# Установить языковые флаги при сборке для всех конфигураций. Эти флаги будут передаваться при всех вызовах компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -lwinpthread")

# Задать имя приложения
set(Application_Name "search_engine")
# Задать переменную списка директорий с заголовками
set(Include_Directories "")
# Добавить директории с заголовками
LIST(APPEND Include_Directories ${CMAKE_SOURCE_DIR}/include)
LIST(APPEND Include_Directories ${CMAKE_SOURCE_DIR}/src)

# В зависимости от добавления библиотеки в проект, закомментировать-раскомментировать if-endif и find_package
#find_package(nlohmann_json REQUIRED)
if (NOT TARGET nlohmann_json)
    add_subdirectory(./libraries/nlohmann_json)
endif()
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(JSON_Install ON CACHE INTERNAL "")

set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
find_package(Boost REQUIRED)

# В зависимости от добавления библиотеки в проект, закомментировать-раскомментировать if-endif и find_package
#find_package(kav_check REQUIRED)
if (NOT TARGET kav_check)
    add_subdirectory(./libraries/kav_check)
endif()
set(check_Install ON CACHE INTERNAL "")

# В зависимости от добавления библиотеки в проект, закомментировать-раскомментировать if-endif и find_package
#find_package(kav_logger REQUIRED)
if (NOT TARGET kav_logger)
    add_subdirectory(./libraries/kav_logger)
endif()
set(logger_Install ON CACHE INTERNAL "")

add_subdirectory(src)

add_subdirectory(tests)

# Указать библиотеки, которые нужно использовать при компоновке заданной цели и/или её зависимостей
target_link_libraries(${Application_Name} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${Application_Name} PRIVATE kav_check::kav_check)
target_link_libraries(${Application_Name} PRIVATE kav_logger::kav_logger)



#Допустим, ваш проект использует add_subdirectory(libA) и add_subdirectory(libB), но libA также использует add_subdirectory(libB)
#https://codengineering.net/q/cmake-and-finding-other-projects-and-their-dependencies-4678
#https://giters.com/cpm-cmake/CPM.cmake/issues/192
#https://qarchive.ru/553594_cmake__kak_ustanovit__zavisimosti_source__library_i_cmakelists_txt_
#https://cgold.readthedocs.io/en/latest/tutorials/install/managing-dependencies/bad.html
#https://galowicz.de/2023/01/23/mixed-cpp-monorepo-project/
#https://reddeveloper.ru/questions/cmake-add-subdirectory-dvazhdy-kak-obshchii-proyekt-5y93M
#https://askdev.ru/q/cmake-kak-nastroit-istochnik-biblioteku-i-cmakelists-zavisimosti-tht-324098/
#https://www.developerload.com/cmake-and-finding-other-projects-and-their-dependencies
#https://ask-dev.ru/info/553594/cmake-how-to-setup-source-library-and-cmakeliststxt-dependencies
#https://www.linuxfixes.com/2021/11/solved-cmake-include-paths-library-that.html
#https://stackoverflow.com/questions/44849511/multiple-sub-projects-depending-on-the-same-library
#https://stackoverflow.com/questions/52458581/cmake-why-is-an-added-subdirectory-not-visible-to-other-subdirectories
#https://ftp.zhirov.kz/books/IT/Other/Система%20построения%20проектов%20CMake%20%28Д.В.%20Дубров%29.pdf

#https://stackoverflow.com/questions/65910460/cmake-error-install-export-includes-target-which-requires-target-that-is-not-in
#https://stackoverflow.com/questions/69996240/cmake-target-links-to-transitive-dependency-target-but-the-target-was-not-found
#https://stackoverflow.com/questions/13703647/how-to-properly-add-include-directories-with-cmake
#https://blog.feabhas.com/2021/08/cmake-part-3-source-file-organisation/
#https://habr.com/ru/articles/683204/
#https://habr.com/ru/articles/904992/
#https://www.ravbug.com/tutorials/cmake-easy/
#https://dzen.ru/a/Z4F5jA1ZrBLS3K39
#https://www.iditect.com/program-example/add-source-in-a-subdirectory-to-a-cmake-project.html
#https://dominikberner.ch/cmake-library-setup/
#https://chat01.ai/en/chat/01JA61BBV9FC5CPXG9K4R26R9K
#https://www.cyberforum.ru/blogs/2396861/10386.html
#https://stackoverflow.com/questions/8304190/cmake-with-include-and-source-paths-basic-setup
#
#
#
#
#
#https://decovar.dev/blog/2023/07/22/cmake-target-link-libraries-scopes/