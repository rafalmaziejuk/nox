# -------------------------------------------------------------
# Create nox-common target
# -------------------------------------------------------------
add_library(${NOX_COMMON_LIB_NAME} STATIC)
target_include_directories(
    ${NOX_COMMON_LIB_NAME}
    PRIVATE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)

nox_append_global_list(NOX_INSTALLATION_TARGETS ${NOX_LIB_NAME})

# -------------------------------------------------------------
# Specify compile options
# -------------------------------------------------------------
target_compile_features(${NOX_COMMON_LIB_NAME} PRIVATE cxx_std_20)

target_compile_options(
    ${NOX_COMMON_LIB_NAME}
    PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>: /W4>
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
)

if(NOX_ENABLE_COVERAGE)
    target_compile_options(
        ${NOX_COMMON_LIB_NAME}
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>: -O0 -g --coverage>
    )
    target_link_libraries(
        ${NOX_COMMON_LIB_NAME}
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>: --coverage>
    )
endif()

# -------------------------------------------------------------
# Specify compile definitions
# -------------------------------------------------------------
target_compile_definitions(
    ${NOX_COMMON_LIB_NAME}
    PUBLIC
    # Windows specific definitions
    $<$<PLATFORM_ID:Windows>: WIN32_LEAN_AND_MEAN>

    # Configuration specific definitions
    $<$<CONFIG:Debug>: NOX_DEBUG>

    # Options specific definitions
    $<$<BOOL:${BUILD_SHARED_LIBS}>: NOX_SHARED>
    $<$<BOOL:${NOX_ENABLE_LOGGING}>: NOX_ENABLE_LOGGING>
)

# -------------------------------------------------------------
# Set properties
# -------------------------------------------------------------
set_target_properties(
    ${NOX_COMMON_LIB_NAME}
    PROPERTIES
    VERSION "${NOX_VERSION}"
    SOVERSION "${NOX_VERSION_MAJOR}.${NOX_VERSION_MINOR}"
    DEBUG_POSTFIX "${NOX_DEBUG_POSTFIX}"
    FOLDER "${NOX_FOLDER_NAME}"
)

# -------------------------------------------------------------
# Link libraries
# -------------------------------------------------------------
target_link_libraries(
    ${NOX_COMMON_LIB_NAME}
    PRIVATE
    ${NOX_INTERFACE_LIB_NAME}
)

# -------------------------------------------------------------
# Add sources
# -------------------------------------------------------------
set(NOX_COMMON_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logger.h
)

target_sources(${NOX_COMMON_LIB_NAME} PRIVATE ${NOX_COMMON_SOURCES})

# -------------------------------------------------------------
# Create Visual Studio project source tree
# -------------------------------------------------------------
file(GLOB_RECURSE NOX_PUBLIC_HEADERS "${PROJECT_SOURCE_DIR}/include/nox/*.h")	
target_sources(${NOX_LIB_NAME} PRIVATE ${NOX_PUBLIC_HEADERS})

nox_create_project_source_tree(${NOX_COMMON_LIB_NAME})
