# -------------------------------------------------------------
# Set internal variables
# -------------------------------------------------------------
set(NOX_DEBUG_POSTFIX "-d")

# -------------------------------------------------------------
# Create nox target
# -------------------------------------------------------------
add_library(${NOX_LIB_NAME})
add_library(${NOX_LIB_NAME}::${NOX_LIB_NAME} ALIAS ${NOX_LIB_NAME})
target_include_directories(
    ${NOX_LIB_NAME}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/include>"
    PRIVATE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

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
# Specify compile definitions
# -------------------------------------------------------------
target_compile_definitions(
    ${NOX_LIB_NAME}
    PRIVATE
    # Windows specific definitions
    $<$<PLATFORM_ID:Windows>: WIN32_LEAN_AND_MEAN>

    # Configuration specific definitions
    $<$<CONFIG:Debug>: NOX_DEBUG>

    # Options specific definitions
    $<$<BOOL:${BUILD_SHARED_LIBS}>: NOX_SHARED>
)

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
file(GLOB_RECURSE NOX_PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/nox/*.h")
target_sources(${NOX_LIB_NAME} PRIVATE ${NOX_PUBLIC_HEADERS})

nox_create_project_source_tree(${NOX_LIB_NAME})
