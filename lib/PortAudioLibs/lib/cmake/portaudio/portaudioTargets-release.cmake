#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "portaudio" for configuration "Release"
set_property(TARGET portaudio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(portaudio PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/portaudio_x64.lib"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "winmm;dsound;ole32;uuid;ole32;uuid;setupapi;ole32;uuid"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/portaudio_x64.dll"
  )

list(APPEND _cmake_import_check_targets portaudio )
list(APPEND _cmake_import_check_files_for_portaudio "${_IMPORT_PREFIX}/lib/portaudio_x64.lib" "${_IMPORT_PREFIX}/bin/portaudio_x64.dll" )

# Import target "portaudio_static" for configuration "Release"
set_property(TARGET portaudio_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(portaudio_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LINK_INTERFACE_LIBRARIES_RELEASE "winmm;dsound;ole32;uuid;ole32;uuid;setupapi;ole32;uuid"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/portaudio_static_x64.lib"
  )

list(APPEND _cmake_import_check_targets portaudio_static )
list(APPEND _cmake_import_check_files_for_portaudio_static "${_IMPORT_PREFIX}/lib/portaudio_static_x64.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
