#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ical" for configuration "Release"
set_property(TARGET ical APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ical PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libical.3.0.20.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libical.3.dylib"
  )

list(APPEND _cmake_import_check_targets ical )
list(APPEND _cmake_import_check_files_for_ical "${_IMPORT_PREFIX}/lib/libical.3.0.20.dylib" )

# Import target "ical-static" for configuration "Release"
set_property(TARGET ical-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ical-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libical.a"
  )

list(APPEND _cmake_import_check_targets ical-static )
list(APPEND _cmake_import_check_files_for_ical-static "${_IMPORT_PREFIX}/lib/libical.a" )

# Import target "ical_cxx" for configuration "Release"
set_property(TARGET ical_cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ical_cxx PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libical_cxx.3.0.20.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libical_cxx.3.dylib"
  )

list(APPEND _cmake_import_check_targets ical_cxx )
list(APPEND _cmake_import_check_files_for_ical_cxx "${_IMPORT_PREFIX}/lib/libical_cxx.3.0.20.dylib" )

# Import target "ical_cxx-static" for configuration "Release"
set_property(TARGET ical_cxx-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(ical_cxx-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libical_cxx.a"
  )

list(APPEND _cmake_import_check_targets ical_cxx-static )
list(APPEND _cmake_import_check_files_for_ical_cxx-static "${_IMPORT_PREFIX}/lib/libical_cxx.a" )

# Import target "icalss" for configuration "Release"
set_property(TARGET icalss APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalss PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libicalss.3.0.20.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libicalss.3.dylib"
  )

list(APPEND _cmake_import_check_targets icalss )
list(APPEND _cmake_import_check_files_for_icalss "${_IMPORT_PREFIX}/lib/libicalss.3.0.20.dylib" )

# Import target "icalss-static" for configuration "Release"
set_property(TARGET icalss-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalss-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libicalss.a"
  )

list(APPEND _cmake_import_check_targets icalss-static )
list(APPEND _cmake_import_check_files_for_icalss-static "${_IMPORT_PREFIX}/lib/libicalss.a" )

# Import target "icalss_cxx" for configuration "Release"
set_property(TARGET icalss_cxx APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalss_cxx PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libicalss_cxx.3.0.20.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libicalss_cxx.3.dylib"
  )

list(APPEND _cmake_import_check_targets icalss_cxx )
list(APPEND _cmake_import_check_files_for_icalss_cxx "${_IMPORT_PREFIX}/lib/libicalss_cxx.3.0.20.dylib" )

# Import target "icalss_cxx-static" for configuration "Release"
set_property(TARGET icalss_cxx-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalss_cxx-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libicalss_cxx.a"
  )

list(APPEND _cmake_import_check_targets icalss_cxx-static )
list(APPEND _cmake_import_check_files_for_icalss_cxx-static "${_IMPORT_PREFIX}/lib/libicalss_cxx.a" )

# Import target "icalvcal" for configuration "Release"
set_property(TARGET icalvcal APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalvcal PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libicalvcal.3.0.20.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libicalvcal.3.dylib"
  )

list(APPEND _cmake_import_check_targets icalvcal )
list(APPEND _cmake_import_check_files_for_icalvcal "${_IMPORT_PREFIX}/lib/libicalvcal.3.0.20.dylib" )

# Import target "icalvcal-static" for configuration "Release"
set_property(TARGET icalvcal-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(icalvcal-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libicalvcal.a"
  )

list(APPEND _cmake_import_check_targets icalvcal-static )
list(APPEND _cmake_import_check_files_for_icalvcal-static "${_IMPORT_PREFIX}/lib/libicalvcal.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
