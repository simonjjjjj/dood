#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "threepp::threepp" for configuration "Debug"
set_property(TARGET threepp::threepp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(threepp::threepp PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/threepp.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "glfw"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/threepp.dll"
  )

list(APPEND _cmake_import_check_targets threepp::threepp )
list(APPEND _cmake_import_check_files_for_threepp::threepp "${_IMPORT_PREFIX}/debug/lib/threepp.lib" "${_IMPORT_PREFIX}/debug/bin/threepp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
