cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

# -------------------------------------------------------------
# Include modules
# -------------------------------------------------------------
include(CMakeDependentOption)

# -------------------------------------------------------------
# Start project
# -------------------------------------------------------------
project(nox LANGUAGES CXX)

# -------------------------------------------------------------
# Set global properties and variables
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
# Specify options
# -------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

cmake_dependent_option(NOX_PLATFORM_WINDOWS "Target platform Windows" ON "WIN32" OFF)
cmake_dependent_option(NOX_PLATFORM_LINUX "Target platform Linux" ON "UNIX" OFF)

# -------------------------------------------------------------
# Print settings
# -------------------------------------------------------------
message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
message(STATUS "NOX_PLATFORM_WINDOWS = ${NOX_PLATFORM_WINDOWS}")
message(STATUS "NOX_PLATFORM_LINUX = ${NOX_PLATFORM_LINUX}")
