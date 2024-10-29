cmake_minimum_required(VERSION 3.24.0 FATAL_ERROR)

# -------------------------------------------------------------
# Include modules
# -------------------------------------------------------------
include(CMakeDependentOption)
include(FetchContent)
include(GenerateExportHeader)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(common)

# -------------------------------------------------------------
# Start project
# -------------------------------------------------------------
nox_extract_version()
project(nox VERSION ${NOX_VERSION} LANGUAGES CXX)

if(NOX_COPY_GIT_HOOKS)
    nox_setup_git_hooks()
endif()

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

set(NOX_MAIN_PROJECT OFF)
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(NOX_MAIN_PROJECT ON)
endif()

# -------------------------------------------------------------
# Set global variables
# -------------------------------------------------------------
set(NOX_INSTALLATION_TARGETS "")
set(NOX_LIB_NAME "nox")

set(NOX_FOLDER_NAME "${NOX_LIB_NAME}")
set(NOX_THIRD_PARTY_FOLDER_NAME "${NOX_FOLDER_NAME}/third_party")

# -------------------------------------------------------------
# Specify options
# -------------------------------------------------------------
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(NOX_INSTALL "Generate installation target" ${NOX_MAIN_PROJECT})
option(NOX_BUILD_SANDBOX "Generate sandbox target" OFF)
option(NOX_BUILD_TESTS "Generate test targets" OFF)
option(NOX_BUILD_DOCS "Generate documentation target" OFF)
option(NOX_ENABLE_COVERAGE "Enable tests coverage." OFF)

cmake_dependent_option(NOX_PLATFORM_WINDOWS "Target platform Windows" ON "WIN32" OFF)
cmake_dependent_option(NOX_PLATFORM_LINUX "Target platform Linux" ON "UNIX" OFF)

# -------------------------------------------------------------
# Print project information
# -------------------------------------------------------------
message(STATUS "nox ${NOX_VERSION}")
message(STATUS "NOX_INSTALL = ${NOX_INSTALL}")
message(STATUS "NOX_BUILD_SANDBOX = ${NOX_BUILD_SANDBOX}")
message(STATUS "NOX_BUILD_TESTS = ${NOX_BUILD_TESTS}")
message(STATUS "NOX_BUILD_DOCS = ${NOX_BUILD_DOCS}")
message(STATUS "NOX_ENABLE_COVERAGE = ${NOX_ENABLE_COVERAGE}")
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

if(NOX_BUILD_TESTS)
    add_subdirectory(tests)
endif()

if(NOX_BUILD_DOCS)
    add_subdirectory(docs)
endif()

# -------------------------------------------------------------
# Specify installation options
# -------------------------------------------------------------
if(NOX_INSTALL)
    include(GNUInstallDirs)

    install(
        TARGETS ${NOX_INSTALLATION_TARGETS}
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    )

    install(
        DIRECTORY "${PROJECT_SOURCE_DIR}/include/nox"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h"
    )
endif()
