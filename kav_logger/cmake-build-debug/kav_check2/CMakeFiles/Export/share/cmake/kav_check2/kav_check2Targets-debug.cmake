#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "kav_check2::kav_check2" for configuration "Debug"
set_property(TARGET kav_check2::kav_check2 APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(kav_check2::kav_check2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libkav_check2d.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS kav_check2::kav_check2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_kav_check2::kav_check2 "${_IMPORT_PREFIX}/lib/libkav_check2d.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
