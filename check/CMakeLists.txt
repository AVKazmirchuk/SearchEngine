cmake_minimum_required(VERSION 3.21)

add_library(check checkFile.cpp checkFileException.h errorCode.h operationFileAndJSON.cpp operationFileAndJSON.h)
#target_include_directories(search_engine PUBLIC ${SE_INCLUDE_DIR})