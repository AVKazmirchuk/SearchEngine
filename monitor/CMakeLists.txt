set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../runtime")

set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
set(Boost_LIBRARY_DIR "C:\\boost_1_87_0\\stage\\lib")

find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

#target_link_libraries(search_engine_monitor ${Boost_LIBRARIES})

add_executable(search_engine_monitor main.cpp  monitorReceiver.h monitorReceiver.cpp termcolor.h monitor.cpp monitor.h general.h general.cpp readWriteJSONFile.h readWriteJSONFile.cpp checkFileException.h)
target_link_libraries(search_engine_monitor PRIVATE nlohmann_json::nlohmann_json)

