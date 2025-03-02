# -------------------------------------------------------------
# Set internal variables
# -------------------------------------------------------------
set(NOX_DEBUG_POSTFIX "-d")
set(NOX_INTERFACE_LIB_NAME "nox-interface")
set(NOX_COMMON_LIB_NAME "nox-common")

# -------------------------------------------------------------
# Create nox-interface target
# -------------------------------------------------------------
add_library(${NOX_INTERFACE_LIB_NAME} INTERFACE)
target_include_directories(
    ${NOX_INTERFACE_LIB_NAME}
    INTERFACE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>"
)

# -------------------------------------------------------------
# Create nox target
# -------------------------------------------------------------
add_library(${NOX_LIB_NAME})
add_library(${NOX_LIB_NAME}::${NOX_LIB_NAME} ALIAS ${NOX_LIB_NAME})

nox_append_global_list(NOX_INSTALLATION_TARGETS ${NOX_LIB_NAME})

# -------------------------------------------------------------
# Specify compile options
# -------------------------------------------------------------
target_compile_features(${NOX_LIB_NAME} PRIVATE cxx_std_20)

target_compile_options(
    ${NOX_LIB_NAME}
    PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>: /W4>
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
)

if(NOX_ENABLE_COVERAGE)
    target_compile_options(
        ${NOX_LIB_NAME}
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>: -O0 -g --coverage>
    )
    target_link_libraries(
        ${NOX_LIB_NAME}
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>: --coverage>
    )
endif()

# -------------------------------------------------------------
# Set properties
# -------------------------------------------------------------
set_target_properties(
    ${NOX_LIB_NAME}
    PROPERTIES
    VERSION "${NOX_VERSION}"
    SOVERSION "${NOX_VERSION_MAJOR}.${NOX_VERSION_MINOR}"
    DEBUG_POSTFIX "${NOX_DEBUG_POSTFIX}"
    FOLDER "${NOX_FOLDER_NAME}"
)

# -------------------------------------------------------------
# Generate files
# -------------------------------------------------------------
generate_export_header(
    ${NOX_LIB_NAME}
    EXPORT_MACRO_NAME NOX_EXPORT
    EXPORT_FILE_NAME "${PROJECT_SOURCE_DIR}/include/nox/export.h"
)

# -------------------------------------------------------------
# Link libraries
# -------------------------------------------------------------
target_link_libraries(
    ${NOX_LIB_NAME}
    PUBLIC
    ${NOX_INTERFACE_LIB_NAME}
    
    PRIVATE
    ${NOX_COMMON_LIB_NAME}
)

# -------------------------------------------------------------
# Add subdirectories
# -------------------------------------------------------------
add_subdirectory(common)

# -------------------------------------------------------------
# Add sources
# -------------------------------------------------------------
set(NOX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/dummy.cpp
)

target_sources(${NOX_LIB_NAME} PRIVATE ${NOX_SOURCES})

# -------------------------------------------------------------
# Create Visual Studio project source tree
# -------------------------------------------------------------
nox_create_project_source_tree(${NOX_LIB_NAME})
