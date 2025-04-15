set(Boost_INCLUDE_DIR "C:\\boost_1_87_0")
set(Boost_LIBRARY_DIR "C:\\boost_1_87_0\\stage\\lib")

find_package(Boost COMPONENTS REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

#target_link_libraries(search_engine_monitor ${Boost_LIBRARIES})

add_executable(search_engine_monitor main.cpp ../include/monitorSender.h monitorReceiver.h monitorReceive.cpp)


