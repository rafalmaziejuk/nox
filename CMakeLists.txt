cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

# -------------------------------------------------------------
# Include modules
# -------------------------------------------------------------
include(CMakeDependentOption)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(common)

# -------------------------------------------------------------
# Start project
# -------------------------------------------------------------
nox_extract_version()
project(nox VERSION ${NOX_VERSION} LANGUAGES CXX)

# -------------------------------------------------------------
# Set global properties
# -------------------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")

if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES "Release;Debug")
endif()
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type: [Release, Debug]" FORCE)
endif()

# -------------------------------------------------------------
# Set global variables
# -------------------------------------------------------------
set(NOX_LIB_NAME "nox")

set(NOX_FOLDER_NAME "${NOX_LIB_NAME}")

# -------------------------------------------------------------
# Specify options
# -------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(NOX_BUILD_SANDBOX "Build sandbox project" OFF)

cmake_dependent_option(NOX_PLATFORM_WINDOWS "Target platform Windows" ON "WIN32" OFF)
cmake_dependent_option(NOX_PLATFORM_LINUX "Target platform Linux" ON "UNIX" OFF)

# -------------------------------------------------------------
# Print project information
# -------------------------------------------------------------
message(STATUS "nox ${NOX_VERSION}")
message(STATUS "NOX_BUILD_SANDBOX = ${NOX_BUILD_SANDBOX}")
message(STATUS "NOX_PLATFORM_WINDOWS = ${NOX_PLATFORM_WINDOWS}")
message(STATUS "NOX_PLATFORM_LINUX = ${NOX_PLATFORM_LINUX}")
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")

# -------------------------------------------------------------
# Add subdirectories
# -------------------------------------------------------------
add_subdirectory(src)

if(NOX_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()
