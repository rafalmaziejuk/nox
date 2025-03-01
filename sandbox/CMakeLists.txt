# -------------------------------------------------------------
# Create sandbox target
# -------------------------------------------------------------
add_executable(sandbox)

# -------------------------------------------------------------
# Specify compile options
# -------------------------------------------------------------
target_compile_features(sandbox PRIVATE cxx_std_20)

# -------------------------------------------------------------
# Set properties
# -------------------------------------------------------------
set_target_properties(sandbox PROPERTIES FOLDER "${NOX_FOLDER_NAME}")

if(MSVC)
    set_property(
        DIRECTORY ${PROJECT_SOURCE_DIR}
        PROPERTY VS_STARTUP_PROJECT sandbox
    )
endif()

# -------------------------------------------------------------
# Link libraries
# -------------------------------------------------------------
target_link_libraries(
    sandbox
    PRIVATE
    ${NOX_LIB_NAME}
)

# -------------------------------------------------------------
# Add sources
# -------------------------------------------------------------
set(NOX_SANDBOX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_sources(sandbox PRIVATE ${NOX_SANDBOX_SOURCES})

# -------------------------------------------------------------
# Create Visual Studio project source tree
# -------------------------------------------------------------
nox_create_project_source_tree(sandbox)
