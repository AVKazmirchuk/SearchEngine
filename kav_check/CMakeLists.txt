cmake_minimum_required(VERSION 3.21)

project(kav_check VERSION 1.0.0 LANGUAGES CXX)

# for CMAKE_INSTALL_INCLUDEDIR definition
include(GNUInstallDirs)

# указать стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/detail
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

























#https://decovar.dev/blog/2021/03/08/cmake-cpp-library/#the-library