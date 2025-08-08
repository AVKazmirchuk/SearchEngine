# Сформировать список поддиректорий текущей директории, рекурсивно
function(Collect_Subdirectories result curdir)
    FILE(GLOB_RECURSE children LIST_DIRECTORIES true CONFIGURE_DEPENDS ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist} PARENT_SCOPE)
endfunction()

# Предоставляет удобные команды, предназначенные для отладки, для вывода значений свойств и переменных
include(CMakePrintHelpers)

# Задать имя приложения
set(Application_Name_Test "kav_check_test")
# Задать переменную списка директорий с заголовками
set(Include_Directories "")
# Добавить директории с заголовками
LIST(APPEND Include_Directories ${CMAKE_CURRENT_SOURCE_DIR}/include)
LIST(APPEND Include_Directories ${CMAKE_CURRENT_SOURCE_DIR})
LIST(APPEND Include_Directories ${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_disable_pthreads on)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)



#file(GLOB CPP_CONVERTER_JSON CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/converterJSON/*.cpp")
#file(GLOB CPP_INVERTED_INDEX CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/invertedIndex/*.cpp")
#file(GLOB CPP_RELEVANT_RESPONSE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/relevantResponse/*.cpp")
#file(GLOB CPP_PREPARED_REQUEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/*.cpp")
file(GLOB_RECURSE CPP_CHECK_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
#file(GLOB CPP_DOCUMENTS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/documents/*.cpp")
#file(GLOB CPP_REQUESTS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/requests/*.cpp")
#file(GLOB CPP_SEARCH_ENGINE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/searchEngine/*.cpp")
#file(GLOB CPP_READ_WRITE_JSON_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/dispatcherDetermineValidity/*.cpp")
#file(GLOB CPP_READ_TEXT_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/readTextFile/*.cpp")
#file(GLOB CPP_LOGGER CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/Logger/*.cpp")
#file(GLOB CPP_GENERAL CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/general/*.cpp")
#file(GLOB CPP_MONITOR CONFIGURE_DEPENDS "../kav_logger/src/monitorSender/*.cpp")

add_executable(${Application_Name_Test} test.cpp testCheckFile.cpp
        #${CPP_CONVERTER_JSON}
        #${CPP_INVERTED_INDEX}
        #${CPP_RELEVANT_RESPONSE}
        #${CPP_PREPARED_REQUEST}
        ${CPP_CHECK_FILE}
        #${CPP_DOCUMENTS}
        #${CPP_REQUESTS}
        #${CPP_SEARCH_ENGINE}
        #${CPP_READ_WRITE_JSON_FILE}
        #${CPP_READ_TEXT_FILE}
        #${CPP_LOGGER}
        #${CPP_MONITOR}
        #${CPP_GENERAL} testRelevantResponse.cpp testGeneral.cpp testCheckFilePathAndRequestsArrays.cpp testGeneral.h testCheckSetAnswers.cpp main.cpp
)

# Задать переменную списка поддиректорий с заголовками
set(Include_Subdirectories "")
foreach(subdirectory ${Include_Directories})
    set(subdirectory_List "")
    Collect_Subdirectories(subdirectory_List ${subdirectory})
    LIST(APPEND Include_Subdirectories ${subdirectory_List} ${subdirectory})
endforeach()

# Для отладки. Пока оставлю
cmake_print_variables(Include_Subdirectories)

# Добавить к цели директории с заголовками
target_include_directories(${Application_Name_Test} PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(${Application_Name_Test} PUBLIC ${Include_Subdirectories})

target_link_libraries(${Application_Name_Test} PRIVATE nlohmann_json::nlohmann_json)

#target_link_libraries(kav_check_test ${Boost_LIBRARIES})

target_link_libraries(${Application_Name_Test} PRIVATE gtest_main)

include(GoogleTest)

gtest_discover_tests(${Application_Name_Test})









