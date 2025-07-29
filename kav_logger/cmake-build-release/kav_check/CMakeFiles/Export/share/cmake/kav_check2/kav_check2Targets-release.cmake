#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "kav_check2::kav_check2" for configuration "Release"
set_property(TARGET kav_check2::kav_check2 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(kav_check2::kav_check2 PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libkav_check2.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS kav_check2::kav_check2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_kav_check2::kav_check2 "${_IMPORT_PREFIX}/lib/libkav_check2.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
