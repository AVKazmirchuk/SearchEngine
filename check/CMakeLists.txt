cmake_minimum_required(VERSION 3.21)

project(check VERSION 1.0.0)

add_library(check SHARED checkFile.cpp checkFileException.h errorCode.h operationFileAndJSON.cpp operationFileAndJSON.h types.h)

set_target_properties(check PROPERTIES PUBLIC_HEADER operationFileAndJSON.h)

include(GNUInstallDirs)

install(TARGETS check LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(check.pc.in check.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/check.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
#









#как правильно написать библиотеку (файлы h и cpp) для подключения к другим проектам с++ clion
#https://iu5edu.ru/wiki/cpp2/docs/labs/lab1/Instructions/UseStaticLib/
#https://stackoverflow.com/questions/44998233/add-external-c-libraries-to-a-clion-project
#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://stackoverflow.com/questions/29355937/clion-and-cmake-only-building-a-library-without-an-executable/30473299#30473299


























#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://stackoverflow.com/questions/29355937/clion-and-cmake-only-building-a-library-without-an-executable/30473299#30473299
