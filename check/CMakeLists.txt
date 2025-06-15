cmake_minimum_required(VERSION 3.21)

project(check VERSION 1.0.0)
add_library(check checkFile.cpp checkFileException.h errorCode.h operationFileAndJSON.cpp operationFileAndJSON.h types.h)
#target_include_directories(search_engine PUBLIC ${SE_INCLUDE_DIR})
#
#как правильно написать библиотеку (файлы h и cpp) для подключения к другим проектам с++ clion
#https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
#https://stackoverflow.com/questions/29355937/clion-and-cmake-only-building-a-library-without-an-executable/30473299#30473299
