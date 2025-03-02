# -------------------------------------------------------------
# Set internal variables
# -------------------------------------------------------------
set(NOX_UNIT_TESTS_EXE_NAME "unit-tests")

# -------------------------------------------------------------
# Create unit tests target
# -------------------------------------------------------------
add_executable(${NOX_UNIT_TESTS_EXE_NAME})
target_include_directories(
    ${NOX_UNIT_TESTS_EXE_NAME}
    PRIVATE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
)

gtest_discover_tests(${NOX_UNIT_TESTS_EXE_NAME})

# -------------------------------------------------------------
# Specify compile options
# -------------------------------------------------------------
target_compile_features(${NOX_UNIT_TESTS_EXE_NAME} PUBLIC cxx_std_20)

if(NOX_ENABLE_COVERAGE)
    target_compile_options(
        ${NOX_UNIT_TESTS_EXE_NAME}
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>: -O0 -g --coverage>
    )

    target_link_libraries(
        ${NOX_UNIT_TESTS_EXE_NAME}
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU>: --coverage>
    )
endif()

# -------------------------------------------------------------
# Specify compile definitions
# -------------------------------------------------------------
if(BUILD_SHARED_LIBS)
    target_compile_definitions(${NOX_UNIT_TESTS_EXE_NAME} PRIVATE GTEST_LINKED_AS_SHARED_LIBRARY)
endif()

# -------------------------------------------------------------
# Link libraries
# -------------------------------------------------------------
target_link_libraries(
    ${NOX_UNIT_TESTS_EXE_NAME}
    PRIVATE
    GTest::gtest_main
    GTest::gmock_main
    nox
    nox-common
)

# -------------------------------------------------------------
# Set properties
# -------------------------------------------------------------
set_target_properties(${NOX_UNIT_TESTS_EXE_NAME} PROPERTIES FOLDER ${NOX_TESTS_FOLDER_NAME})

# -------------------------------------------------------------
# Generate files
# -------------------------------------------------------------
target_precompile_headers(
    ${NOX_UNIT_TESTS_EXE_NAME}
    PRIVATE
    <array>
    <algorithm>
    <cstdint>
    <memory>
    <string>
    <string_view>
    <unordered_map>
    <utility>
    <vector>
)

# -------------------------------------------------------------
# Add sources
# -------------------------------------------------------------
set(NOX_UNIT_TESTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logger_tests.cpp
)

target_sources(${NOX_UNIT_TESTS_EXE_NAME} PRIVATE ${NOX_UNIT_TESTS_SOURCES})

# -------------------------------------------------------------
# Create Visual Studio project source tree
# -------------------------------------------------------------
nox_create_project_source_tree(${NOX_UNIT_TESTS_EXE_NAME})

# -------------------------------------------------------------
# Create custom target for running unit tests
# -------------------------------------------------------------
add_custom_target(
    run-${NOX_UNIT_TESTS_EXE_NAME}
    COMMAND ${NOX_UNIT_TESTS_EXE_NAME}
)

set_target_properties(
    run-${NOX_UNIT_TESTS_EXE_NAME}
    PROPERTIES
    FOLDER "${NOX_TESTS_FOLDER_NAME}"
    EXCLUDE_FROM_ALL TRUE
)
