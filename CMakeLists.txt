cmake_minimum_required(VERSION 3.25)

# Project name and version
project(SurroundVirtualizer VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set CMAKE_PREFIX_PATH to help find the libraries
set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/lib/PortAudioLibs;${PROJECT_SOURCE_DIR}/lib/OpenALlibs")

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include/headers
    ${PROJECT_SOURCE_DIR}/lib/PortAudioLibs/include
    ${PROJECT_SOURCE_DIR}/lib/OpenALlibs/include
    ${PROJECT_SOURCE_DIR}/src
)

# Add header and source files
set(HEADERS
    ${PROJECT_SOURCE_DIR}/include/headers/openal_setup.h
    ${PROJECT_SOURCE_DIR}/include/headers/portaudio_setup.h
    ${PROJECT_SOURCE_DIR}/include/headers/hrtf_processor.h
    ${PROJECT_SOURCE_DIR}/include/headers/cli_interface.h
    ${PROJECT_SOURCE_DIR}/include/headers/logging.h
)

set(SOURCES
    ${PROJECT_SOURCE_DIR}/app/main.cpp
    ${PROJECT_SOURCE_DIR}/src/openal_setup.cpp
    ${PROJECT_SOURCE_DIR}/src/portaudio_setup.cpp
    ${PROJECT_SOURCE_DIR}/src/hrtf_processor.cpp
    ${PROJECT_SOURCE_DIR}/src/cli_interface.cpp
)

# Find and link PortAudio library
find_package(PortAudio REQUIRED)
if (NOT PortAudio_FOUND)
    message(FATAL_ERROR "PortAudio not found. Make sure it's installed correctly.")
endif()

# Set PortAudio library path (adjust the path as necessary)
set(PORTAUDIO_LIBRARIES ${PortAudio_LIBRARIES})
set(PORTAUDIO_DLL "${PROJECT_SOURCE_DIR}/lib/PortAudioLibs/bin/portaudio_x64.dll")

# Find and link OpenAL library
find_package(OpenAL REQUIRED)
if (NOT OpenAL_FOUND)
    message(FATAL_ERROR "OpenAL not found. Make sure it's installed correctly.")
endif()

# Set DLL paths
set(OPENAL_DLL "${PROJECT_SOURCE_DIR}/lib/OpenALlibs/bin/OpenAL32.dll")
set(PORTAUDIO_DLL "${PROJECT_SOURCE_DIR}/lib/PortAudioLibs/bin/portaudio_x64.dll")

# Add executable
add_executable(SurroundVirtualizer ${SOURCES} ${HEADERS})

# Link the required libraries to the executable
# Prefer imported targets if available
if (TARGET OpenAL::OpenAL)
    target_link_libraries(SurroundVirtualizer OpenAL::OpenAL)
else()
    target_link_libraries(SurroundVirtualizer ${OPENAL_LIBRARY})
endif()
if (TARGET PortAudio::PortAudio)
    target_link_libraries(SurroundVirtualizer PortAudio::PortAudio)
else()
    target_link_libraries(SurroundVirtualizer ${PORTAUDIO_LIBRARIES} ${PROJECT_SOURCE_DIR}/lib/PortAudioLibs/lib/portaudio_x64.lib)
endif()

# Copy DLLs after build (for all configs)
add_custom_command(TARGET SurroundVirtualizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${OPENAL_DLL}
        $<TARGET_FILE_DIR:SurroundVirtualizer>
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${PORTAUDIO_DLL}
        $<TARGET_FILE_DIR:SurroundVirtualizer>
)

# Set output directories for the build
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

# Display build output directory
message(STATUS "Build output directory: ${CMAKE_BINARY_DIR}/bin")
