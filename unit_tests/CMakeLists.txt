# --------------------------------------------------
# Setup googletest
# --------------------------------------------------
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/b796f7d.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
    
set_target_properties(gtest PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")
set_target_properties(gtest_main PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")
set_target_properties(gmock PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")
set_target_properties(gmock_main PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")
enable_testing()

# --------------------------------------------------
# Create unit tests executable
# --------------------------------------------------
add_executable(${NOX_UNIT_TESTS_EXE_NAME})
target_include_directories(
    ${NOX_UNIT_TESTS_EXE_NAME}
    PRIVATE
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>"
)

# --------------------------------------------------
# Set properties
# --------------------------------------------------
set_target_properties(${NOX_UNIT_TESTS_EXE_NAME} PROPERTIES FOLDER ${NOX_FOLDER_NAME})

# --------------------------------------------------
# Link libraries
# --------------------------------------------------
if(BUILD_SHARED_LIBS)
    target_compile_definitions(${NOX_UNIT_TESTS_EXE_NAME} PRIVATE GTEST_LINKED_AS_SHARED_LIBRARY)
endif()

target_link_libraries(
    ${NOX_UNIT_TESTS_EXE_NAME}
    PRIVATE
    ${NOX_IMPL_LIB_NAME}
    GTest::gtest_main
    GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(${NOX_UNIT_TESTS_EXE_NAME})

# --------------------------------------------------
# Add sources
# --------------------------------------------------
set(NOX_UNIT_TESTS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_sources(${NOX_UNIT_TESTS_EXE_NAME} PRIVATE ${NOX_UNIT_TESTS_SOURCES})

add_subdirectory(mocks)
add_subdirectory(plugins)

nox_create_project_source_tree(${NOX_UNIT_TESTS_EXE_NAME})