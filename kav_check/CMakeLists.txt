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
#
#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#


cmake_minimum_required(VERSION 3.21)
project(kav_check VERSION 1.0.0 LANGUAGES CXX)

#set(DEFAULT_BUILD_TYPE "Release")

#if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
#    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
#    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
#    # Set the possible values of build type for cmake-gui
#   set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
#endif()

# CONFIGURATION

include(GNUInstallDirs)

set(KAV_CHECK_TARGET_NAME ${PROJECT_NAME})
set(KAV_CHECK_INCLUDE_BUILD_DIR "${PROJECT_SOURCE_DIR}/include/")
set(KAV_CHECK_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")

set(SOURCE_FILES src/checkFile.cpp src/operationFileAndJSON.cpp)



message(${PROJECT_SOURCE_DIR})
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${CMAKE_INSTALL_INCLUDEDIR})
message(${PROJECT_NAME})

# TARGET

add_library(${KAV_CHECK_TARGET_NAME} INTERFACE)
#add_library(${PROJECT_NAME}::${KAV_CHECK_TARGET_NAME} ALIAS ${KAV_CHECK_TARGET_NAME})
#set_target_properties(kav_check PROPERTIES PUBLIC_HEADER ${KAV_CHECK_INCLUDE_BUILD_DIR}/kav/operationFileAndJSON.hpp)
target_include_directories(
        ${KAV_CHECK_TARGET_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${KAV_CHECK_INCLUDE_BUILD_DIR}>
        $<INSTALL_INTERFACE:${KAV_CHECK_INCLUDE_INSTALL_DIR}>
        )

#set_target_properties(${PROJECT_NAME} PROPERTIES
#        VERSION ${PROJECT_VERSION}
#        SOVERSION 1)

#install(TARGETS ${PROJECT_NAME} EXPORT MyLibConfig
#        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
#install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

#install(EXPORT MyLibConfig DESTINATION share/MyLib/cmake)

#export(TARGETS ${PROJECT_NAME} FILE MyLibConfig.cmake)























#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://stackoverflow.com/questions/29355937/clion-and-cmake-only-building-a-library-without-an-executable/30473299#30473299
