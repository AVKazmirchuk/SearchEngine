# Установить минимальную версию cmake
cmake_minimum_required(VERSION 3.21)#

# Задать имя для проекта, версию, название языка
project(kav_check VERSION 1.0.0 LANGUAGES CXX)#



# Установить стандарт C++
set(CMAKE_CXX_STANDARD 20)#
# Установить требование стандарта С++
set(CMAKE_CXX_STANDARD_REQUIRED ON)#
# Отключить расширения компилятора
set(CMAKE_CXX_EXTENSIONS OFF)#

# Установить библиотеку как статическую
option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

# Если библиотека разделяемая
if(BUILD_SHARED_LIBS)
    # Добавить в проект библиотеку как разделяемую
    add_library(${PROJECT_NAME} SHARED)
else()
    # Добавить в проект библиотеку как статическую
    add_library(${PROJECT_NAME} STATIC)
endif()

# Добавить в проект библиотеку с возможностью установки подкаталога
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Установить уровни предупреждений для разных компиляторов
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options( kav_check PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    target_compile_options( kav_check PRIVATE -Wweak-vtables -Wexit-time-destructors -Wglobal-constructors -Wmissing-noreturn )
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( kav_check PRIVATE /W4 /w44265 /w44061 /w44062 )
endif()



find_package(nlohmann_json REQUIRED)
set(JSON_BuildTests OFF CACHE INTERNAL "")
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

#if (NOT TARGET nlohmann_json)

#    add_subdirectory(nlohmann_json)
#    set(JSON_BuildTests OFF CACHE INTERNAL "")
#    target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

#endif()



set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
set(Boost_LIBRARY_DIR "C:\\boost_1_87_0\\stage\\lib")
find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})



# Является ли текущий проект проектом верхнего уровня
if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

# Является ли текущий проект проектом верхнего уровня
if (PROJECT_IS_TOP_LEVEL)
    message(STATUS "This project is a top-level one")
else()
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
endif()

# Добавить только исходные тексты
target_sources(${PROJECT_NAME}
        PRIVATE
        src/checkFile.cpp src/operationFileAndJSON.cpp
        )
# Добавить в цель ожидаемые функции компилятора
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)#

# Добавить включаемые каталоги в целевую папку
target_include_directories(${PROJECT_NAME}
        PRIVATE
        # где сама библиотека будет искать свои внутренние заголовки
        ${CMAKE_CURRENT_SOURCE_DIR}/include/kav/detail
        PUBLIC
        # где проект верхнего уровня будет искать общедоступные заголовки библиотеки
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # где внешние проекты будут искать общедоступные заголовки библиотеки
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

# Определить переменные каталога установки
include(GNUInstallDirs)#

message(STATUS ${CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT})
# Изменить путь установки по умолчанию
if(DEFINED CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX is not set\n"
            "Default value: ${CMAKE_INSTALL_PREFIX}\n"
            "Will set it to ${CMAKE_SOURCE_DIR}/install"
    )
    set(CMAKE_INSTALL_PREFIX
            "${CMAKE_SOURCE_DIR}/install"
            CACHE PATH "Where the library will be installed to" FORCE
            )
else()
    message(
            STATUS
            "CMAKE_INSTALL_PREFIX was already set\n"
            "Current value: ${CMAKE_INSTALL_PREFIX}"
    )
endif()

#message(${PROJECT_SOURCE_DIR})
#message(${CMAKE_CURRENT_SOURCE_DIR})
#message(${CMAKE_INSTALL_INCLUDEDIR})
#message(${PROJECT_NAME})

# Прописать заголовки
set(public_headers
        include/kav/operationFileAndJSON.h
        include/kav/detail/checkFileException.h
        include/kav/detail/errorCode.h
        include/kav/detail/types.h
        )

# вариант со свойством PUBLIC_HEADER, к сожалению, не сохраняет структуру папок
# set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")
# поэтому вместо этого мы перебираем общедоступные заголовки и устанавливаем их "вручную".
foreach(header ${public_headers})
    message(${CMAKE_CURRENT_SOURCE_DIR})
    message(${header})
    file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
    get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
    install(FILES ${header} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}")
endforeach()

# Определить отладочный суффикс
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")



# Установить цель и связанные с ней файлы, создать экспортный набор
install(TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}Targets"
        # они получают значения по умолчанию из GNUInstallDirs, устанавливать их не нужно
        #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
        #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
        #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
        # за исключением общедоступных заголовков, поскольку мы хотим, чтобы они находились внутри папки библиотеки
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/имя проекта
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
        )#

# Сгенерировать и установить файл CMake, экспортирующий цели для зависимых проектов
install(EXPORT "${PROJECT_NAME}Targets"
        FILE "${PROJECT_NAME}Targets.cmake"
        # пространство имён библиотеки
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION cmake
        )#

# Включить вспомогательные функции для создания конфигурационных файлов, которые могут быть включены в другие проекты для поиска
# и использования пакета
include(CMakePackageConfigHelpers)#

# Создать файл версии для проекта
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)#
# Создать файл конфигурации для проекта
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION cmake
        )#
# Установить конфигурационные файлы
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION cmake
        )

# Создать цели экспорта для дерева сборки
# (не понятно для чего это нужно, но это вызывает проблемы,
# поэтому пока закомментировано)
#
# Экспортировать цели или пакеты для внешних проектов, чтобы использовать их непосредственно в дереве сборки текущего
# проекта без установки. Создать файл, который может быть включён во внешние проекты для импорта целей из дерева сборки
# текущего проекта
 export(EXPORT "${PROJECT_NAME}Targets"
     FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
     NAMESPACE ${PROJECT_NAME}::
 )



#https://stackoverflow.com/questions/16319292/cmake-error-could-not-load-cache
#https://stackoverflow.com/questions/69338088/error-while-configuring-cmake-project-running-nmake-failed
#https://habr.com/ru/articles/904992/

#c:\nlohmann_json\build>"C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" -S ..\ -B . -DCMAKE_CXX_COMPILER="C:/MinGW-W64/x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev1/bin/c++.exe" -DCMAKE_MAKE_PROGRAM="C:/Program Files/JetBrains/CLion 2021.3.4/bin/ninja/win/ninja.exe" -G Ninja
#c:\nlohmann_json\build>"C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" -DCMAKE_BUILD_TYPE=Debug ..
#c:\nlohmann_json\build>"C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" --build .
#c:\nlohmann_json\build>"C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" --install .
#c:\nlohmann_json\build>"C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" -DCMAKE_BUILD_TYPE=Release ..
#c:\nlohmann_json\build>"C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" --build .
#c:\nlohmann_json\build>"C:\Program Files\JetBrains\CLion 2021.3.4\bin\cmake\win\bin\cmake.exe" --install .

# -DCMAKE_CXX_COMPILER="C:/MinGW-W64/x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev1/bin/c++.exe"
# -DCMAKE_MAKE_PROGRAM="C:/Program Files/JetBrains/CLion 2021.3.4/bin/ninja/win/ninja.exe" -G Ninja
# -DBUILD_SHARED_LIBS=1




#https://superuser.com/questions/1121913/how-do-we-install-new-libraries-for-c-mingw
#https://habr.com/ru/articles/549788/
#https://blog.elijahlopez.ca/posts/vcpkg-cmake-tutorial/
#https://ps-group.github.io/opengl/setup_windows
#https://irendering.net/how-to-install-and-use-a-c-standard-library/
#https://cppscripts.com/how-to-install-cpp-library
#https://ru.stackoverflow.com/questions/848601/Подключение-пакетов-cmake-с-использованием-find-package
#https://habr.com/ru/articles/535602/
#https://cliutils.gitlab.io/modern-cmake/chapters/packages.html
#https://gitlab.kitware.com/cmake/community/-/wikis/doc/tutorials/How-To-Find-Libraries
#https://www.foonathan.net/2016/03/cmake-install/
#https://stackoverflow.com/questions/31537602/how-to-use-cmake-to-find-and-link-to-a-library-using-install-export-and-find-pac

#https://yandex.ru/search/?text=%D0%BA%D0%B0%D0%BA+%D1%83%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%B8%D1%82%D1%8C+%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA%D1%83+%D0%B2+%D1%81%D0%B8%D1%81%D1%82%D0%B5%D0%BC%D1%83+%D0%B4%D0%BB%D1%8F+%D0%B8%D1%81%D0%BF%D0%BE%D0%BB%D1%8C%D0%B7%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F+find_package+%D1%81%2B%2B&lr=38&clid=2270455&win=628

#https://codingnest.com/basic-cmake-part-2/
#https://www.foonathan.net/2016/03/cmake-install/
#https://reddeveloper.ru/questions/cmake-add-library-nikneimy-xXwDq
#https://stackoverflow.com/questions/60607037/how-to-configure-the-cmake-file-correctly-to-build-a-simple-hello-world-for-nloh

#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://iu5edu.ru/wiki/cpp2/docs/labs/lab1/Instructions/StaticLib/
#https://stackoverflow.com/questions/39598323/how-to-properly-link-libraries-with-cmake
#https://habr.com/ru/articles/683204/
#https://eax.me/cmake/
#https://ps-group.github.io/cxx/cmake_cheatsheet
#https://neerc.ifmo.ru/wiki/index.php?title=CMake_Tutorial
#https://iamsorush.com/posts/cpp-cmake-build/
#https://decovar.dev/blog/2021/03/08/cmake-cpp-library/#the-library