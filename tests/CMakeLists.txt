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
set(Application_Name_Test "search_engine_test")
# Задать переменную списка директорий с заголовками
set(Include_Directories_Test "")
# Добавить директории с заголовками. Может что-то лишнее из списка?
#LIST(APPEND Include_Directories_Test ${CMAKE_CURRENT_SOURCE_DIR}/include)
#LIST(APPEND Include_Directories_Test ${CMAKE_CURRENT_SOURCE_DIR})
LIST(APPEND Include_Directories_Test ${CMAKE_SOURCE_DIR}/include)
LIST(APPEND Include_Directories_Test ${CMAKE_SOURCE_DIR}/src)
# Для отладки
message(STATUS "CMAKE_SOURCE_DIR_TEST: ${CMAKE_SOURCE_DIR}")

#Загрузить и запустить код CMake из файла или модуля
include(FetchContent)
#Записать параметры, описывающие способ заполнения указанного контента
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
#Добавьте каталоги include в сборку
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#Отключить поддержку многопоточности в библиотеке Google Test (gtest)
set(gtest_disable_pthreads on)
#Не позволить GoogleTest изменять настройки компилятора и компоновщика при сборке
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#Гарантировать, что к моменту возврата каждая из указанных зависимостей будет доступна для проекта
FetchContent_MakeAvailable(googletest)

#Определить файлы-исходники проекта в переменные
#file(GLOB_RECURSE CPP_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp") # Внимание!!! Добавляет второй раз main.cpp
#Пока сделал простым перечислением всех директорий
#TODO Надо научиться добавлять исключения
file(GLOB CPP_CONVERTER_JSON CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/converterJSON/*.cpp")
file(GLOB CPP_DISPATCHER_OPERATION_VALIDITY CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/dispatcherOperations/*.cpp")
file(GLOB CPP_DOCUMENTS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/documents/*.cpp")
file(GLOB CPP_INVERTED_INDEX CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/invertedIndex/*.cpp")
file(GLOB CPP_RELEVANT_RESPONSE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/relevantResponse/*.cpp")
file(GLOB CPP_PREPARED_REQUEST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/relevantResponse/preparedRequest/*.cpp")
file(GLOB CPP_REQUESTS CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/requests/*.cpp")
file(GLOB CPP_SEARCH_ENGINE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/searchEngine/*.cpp")

#Добавить цель, исполняемый файл, для сборки из исходных файлов, перечисленных в вызове команды
add_executable(${Application_Name_Test} main.cpp test.cpp testGeneral.cpp testInvertedIndex.cpp
        testRelevantResponse.cpp
        ${CPP_CONVERTER_JSON}
        ${CPP_DISPATCHER_OPERATION_VALIDITY}
        ${CPP_DOCUMENTS}
        ${CPP_INVERTED_INDEX}
        ${CPP_RELEVANT_RESPONSE}
        ${CPP_PREPARED_REQUEST}
        ${CPP_REQUESTS}
        ${CPP_SEARCH_ENGINE}
        )

# Задать переменную списка поддиректорий с заголовками
set(Include_Subdirectories "")
foreach(subdirectory ${Include_Directories_Test})
    set(subdirectory_List "")
    Collect_Subdirectories(subdirectory_List ${subdirectory})
    LIST(APPEND Include_Subdirectories ${subdirectory_List} ${subdirectory})
endforeach()

# Для отладки
cmake_print_variables(Include_Subdirectories)

# Добавить к цели директории с заголовками
target_include_directories(${Application_Name_Test} PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(${Application_Name_Test} PUBLIC ${Include_Subdirectories})

#Подключить библиотеку
target_link_libraries(${Application_Name_Test} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${Application_Name_Test} PRIVATE kav_check::kav_check)
target_link_libraries(${Application_Name_Test} PRIVATE kav_logger::kav_logger)
target_link_libraries(${Application_Name_Test} PRIVATE gtest_main)
#Загрузить и запустить код CMake из файла или модуля
include(GoogleTest)
#Автоматически добавить тесты с помощью CTest, запрашивая у скомпилированного исполняемого файла теста информацию о доступных тестах
gtest_discover_tests(${Application_Name_Test})















