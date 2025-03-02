# -------------------------------------------------------------
# Set internal variables
# -------------------------------------------------------------
set(NOX_TESTS_FOLDER_NAME "${NOX_FOLDER_NAME}/tests")

# -------------------------------------------------------------
# Setup GoogleTest
# -------------------------------------------------------------
include(GoogleTest)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/ff233bd.zip
    DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(googletest)

set_target_properties(gtest PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")
set_target_properties(gtest_main PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")
set_target_properties(gmock PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")
set_target_properties(gmock_main PROPERTIES FOLDER "${NOX_THIRD_PARTY_FOLDER_NAME}/gtest")

enable_testing()

# -------------------------------------------------------------
# Add subdirectories
# -------------------------------------------------------------
add_subdirectory(unit_tests)
