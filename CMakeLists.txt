cmake_minimum_required(VERSION 3.25)

# Project name and version
project(SurroundVirtualizer VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include/imports)
include_directories(${PROJECT_SOURCE_DIR}/include/headers)
include_directories(${PROJECT_SOURCE_DIR}/lib/PortAudioLibs/include)
include_directories(${PROJECT_SOURCE_DIR}/lib/OpenALlibs/include)

# Add source files
set(SOURCES
    app/main.cpp
    src/openal_setup.cpp
    src/portaudio_setup.cpp
    src/hrtf_library.cpp
    src/hrtf_processor.cpp
)

# Find PortAudio
find_package(PortAudio REQUIRED)
if (NOT PortAudio_FOUND)
    message(FATAL_ERROR "PortAudio not found. Make sure it's installed correctly.")
endif()

# Set PortAudio library path (adjust the path as necessary)
set(PORTAUDIO_LIBRARIES ${PortAudio_LIBRARIES})
set(PORTAUDIO_DLL "${PROJECT_SOURCE_DIR}/lib/PortAudioLibs/bin/portaudio_x64.dll")

# Add OpenAL library path explicitly
set(OPENAL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/OpenALlibs/include")
set(OPENAL_LIBRARY "${PROJECT_SOURCE_DIR}/lib/OpenALlibs/lib/OpenAL32.lib")

# Include OpenAL directories
include_directories(${OPENAL_INCLUDE_DIR})

# Find OpenAL
find_package(OpenAL REQUIRED)
if (NOT OpenAL_FOUND)
    message(FATAL_ERROR "OpenAL not found. Make sure it's installed correctly.")
endif()

# Add executable
add_executable(SurroundVirtualizer ${SOURCES} "include/headers/hrtf_library.h" "src/hrtf_library.cpp" "include/headers/hrtf_processor.h" "src/hrtf_processor.cpp")

# Link libraries
target_link_libraries(SurroundVirtualizer
    ${OPENAL_LIBRARY}
    ${PROJECT_SOURCE_DIR}/lib/PortAudioLibs/lib/portaudio_x64.lib
)

# Ensure portaudio_x64.dll is copied to the output directory (only to build/bin/Release)
add_custom_command(TARGET SurroundVirtualizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PORTAUDIO_DLL}
    $<TARGET_FILE_DIR:SurroundVirtualizer>
)

# Output directories for the build
set_target_properties(SurroundVirtualizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib
)

# Install target
install(TARGETS SurroundVirtualizer
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

message(STATUS "Build output directory: ${CMAKE_BINARY_DIR}/bin")
