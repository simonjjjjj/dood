#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "threepp::threepp" for configuration "Release"
set_property(TARGET threepp::threepp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(threepp::threepp PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/threepp.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "glfw"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/threepp.dll"
  )

list(APPEND _cmake_import_check_targets threepp::threepp )
list(APPEND _cmake_import_check_files_for_threepp::threepp "${_IMPORT_PREFIX}/lib/threepp.lib" "${_IMPORT_PREFIX}/bin/threepp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
