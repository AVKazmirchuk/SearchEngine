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
set(Application_Name_Test "kav_logger_test")
# Задать переменную списка директорий с заголовками
set(Include_Directories "")
# Добавить директории с заголовками. Может что-то лишнее из списка?
LIST(APPEND Include_Directories ${CMAKE_CURRENT_SOURCE_DIR}/include)
LIST(APPEND Include_Directories ${CMAKE_CURRENT_SOURCE_DIR})
LIST(APPEND Include_Directories ${CMAKE_SOURCE_DIR}/include)

#Загрузить и запустить код CMake из файла или модуля
include(FetchContent)
#Записать параметры, описывающие способ заполнения указанного контента
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG main
#)
#Добавьте каталоги include в сборку
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
#Отключить поддержку многопоточности в библиотеке Google Test (gtest)
set(gtest_disable_pthreads on)
#Не позволить GoogleTest изменять настройки компилятора и компоновщика при сборке
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#Гарантировать, что к моменту возврата каждая из указанных зависимостей будет доступна для проекта
FetchContent_MakeAvailable(googletest)
#Определить файлы-исходники проекта в переменную
file(GLOB_RECURSE CPP_LOGGER_FILE CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")
#Добавить цель, исполняемый файл, для сборки из исходных файлов, перечисленных в вызове команды
add_executable(${Application_Name_Test} main.cpp test.cpp testLogger.cpp testGeneral.cpp
        ${CPP_LOGGER_FILE}
)

# Задать переменную списка поддиректорий с заголовками
set(Include_Subdirectories "")
foreach(subdirectory ${Include_Directories})
    set(subdirectory_List "")
    Collect_Subdirectories(subdirectory_List ${subdirectory})
    LIST(APPEND Include_Subdirectories ${subdirectory_List} ${subdirectory})
endforeach()

# Для отладки
#cmake_print_variables(Include_Subdirectories)

# Добавить к цели директории с заголовками
target_include_directories(${Application_Name_Test} PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(${Application_Name_Test} PUBLIC ${Include_Subdirectories})

#Подключить библиотеку
target_link_libraries(${Application_Name_Test} PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(${Application_Name_Test} PRIVATE kav_fileOperations::kav_fileOperations)
target_link_libraries(${Application_Name_Test} PRIVATE gtest_main)
#Загрузить и запустить код CMake из файла или модуля
include(GoogleTest)
#Автоматически добавить тесты с помощью CTest, запрашивая у скомпилированного исполняемого файла теста информацию о доступных тестах
gtest_discover_tests(${Application_Name_Test} PROPERTIES TEST_DISCOVERY_TIMEOUT 60)









