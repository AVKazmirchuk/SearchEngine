#cmake_minimum_required(VERSION 3.21)

#project(check VERSION 1.0.0)

#include(GNUInstallDirs)

#add_library(check STATIC checkFile.cpp checkFileException.h errorCode.h operationFileAndJSON.cpp operationFileAndJSON.h types.h)

#set_target_properties(check PROPERTIES PUBLIC_HEADER operationFileAndJSON.h)

#target_include_directories(check PRIVATE ..)

#configure_file(check.pc.in check.pc @ONLY)

#install(TARGETS check LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#configure_file(check.pc.in check.pc @ONLY)

#install(FILES ${CMAKE_BINARY_DIR}/check.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)





#как правильно написать библиотеку (файлы h и cpp) для подключения к другим проектам с++ clion
#https://iu5edu.ru/wiki/cpp2/docs/labs/lab1/Instructions/UseStaticLib/
#https://stackoverflow.com/questions/44998233/add-external-c-libraries-to-a-clion-project
#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://stackoverflow.com/questions/29355937/clion-and-cmake-only-building-a-library-without-an-executable/30473299#30473299


cmake_minimum_required(VERSION 3.21)
project(check VERSION 1.0.0 LANGUAGES CXX)

set(DEFAULT_BUILD_TYPE "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

set(SOURCE_FILES checkFile.cpp operationFileAndJSON.cpp )

add_library(${PROJECT_NAME} INTERFACE)

message(${PROJECT_SOURCE_DIR})
message(${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1)

install(TARGETS ${PROJECT_NAME} EXPORT MyLibConfig
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

install(EXPORT MyLibConfig DESTINATION share/MyLib/cmake)

export(TARGETS ${PROJECT_NAME} FILE MyLibConfig.cmake)























#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://stackoverflow.com/questions/29355937/clion-and-cmake-only-building-a-library-without-an-executable/30473299#30473299
