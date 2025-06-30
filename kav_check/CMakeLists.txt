cmake_minimum_required(VERSION 3.21)

project(kav_check VERSION 1.0.0 LANGUAGES CXX)

# for CMAKE_INSTALL_INCLUDEDIR definition
include(GNUInstallDirs)

# указать стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (NOT TARGET nlohmann_json)

add_subdirectory(nlohmann_json)
set(JSON_BuildTests OFF CACHE INTERNAL "")
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)

endif()



if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
        message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
        message(STATUS "This project is a top-level one")
endif()

# here you can see how instead of writing "SomeLibrary"
# we can just use the PROJECT_NAME variable
add_library(${PROJECT_NAME})



# no need to add headers here, only sources are required
target_sources(${PROJECT_NAME}
        PRIVATE
        src/checkFile.cpp src/operationFileAndJSON.cpp
        )

target_include_directories(${PROJECT_NAME}
        PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/include/kav/detail
        PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

# note that it is not CMAKE_INSTALL_PREFIX we are checking here
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

# without it public headers won't get installed
set(public_headers
        include/kav/operationFileAndJSON.h
        )



message(${PROJECT_SOURCE_DIR})
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${CMAKE_INSTALL_INCLUDEDIR})
message(${PROJECT_NAME})

# the variant with PUBLIC_HEADER property unfortunately does not preserve the folder structure
#set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")
# so instead we iterate through public headers and install them "manually"
foreach(header ${public_headers})
        message(${CMAKE_CURRENT_SOURCE_DIR})
        message(${header})
        file(RELATIVE_PATH header_file_path "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}" "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
        get_filename_component(header_directory_path "${header_file_path}" DIRECTORY)
        install(
                FILES ${header}
                DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${header_directory_path}"
        )
endforeach()

set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")


# install the target and create export-set
install(TARGETS ${PROJECT_NAME}
        EXPORT "${PROJECT_NAME}Targets"
        # these get default values from GNUInstallDirs, no need to set them
        #RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
        #LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
        #ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
        # except for public headers, as we want them to be inside a library folder
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/SomeLibrary
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
        )

# generate and install export file
install(EXPORT "${PROJECT_NAME}Targets"
        FILE "${PROJECT_NAME}Targets.cmake"
#        NAMESPACE ${namespace}::
        DESTINATION cmake
        )

include(CMakePackageConfigHelpers)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)
# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        INSTALL_DESTINATION cmake
        )
# install config files
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION cmake
        )
# generate the export targets for the build tree
# (can't say what this one is for, but so far it has been only causing me problems,
# so I stopped adding it to projects)
# export(EXPORT "${PROJECT_NAME}Targets"
#     FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}Targets.cmake"
#     NAMESPACE ${namespace}::
#)







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