#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "kav_check::kav_check" for configuration "Debug"
set_property(TARGET kav_check::kav_check APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(kav_check::kav_check PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libkav_checkd.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS kav_check::kav_check )
list(APPEND _IMPORT_CHECK_FILES_FOR_kav_check::kav_check "${_IMPORT_PREFIX}/lib/libkav_checkd.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
