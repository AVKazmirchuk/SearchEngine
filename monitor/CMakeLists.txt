set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../runtime")

add_executable(search_engine_monitor main.cpp  monitorReceiver.h monitorReceiver.cpp termcolor.h monitor.cpp monitor.h general.h general.cpp)

set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
set(Boost_LIBRARY_DIR "C:\\boost_1_87_0\\stage\\lib")

find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

find_package(nlohmann_json REQUIRED)
set(JSON_BuildTests OFF CACHE INTERNAL "")
target_link_libraries(search_engine_monitor PRIVATE nlohmann_json::nlohmann_json)

find_package(kav_check REQUIRED)
target_link_libraries(search_engine_monitor PRIVATE kav_check::kav_check)

#target_link_libraries(search_engine_monitor ${Boost_LIBRARIES})


#target_link_libraries(search_engine_monitor PRIVATE nlohmann_json::nlohmann_json)

