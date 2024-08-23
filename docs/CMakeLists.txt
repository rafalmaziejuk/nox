# -------------------------------------------------------------
# Find Doxygen
# -------------------------------------------------------------
set(DOXYGEN_SKIP_DOT TRUE)
find_package(Doxygen REQUIRED)

if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen not found")
endif()

# -------------------------------------------------------------
# Create command and target for documentation generation
# -------------------------------------------------------------
configure_file(Doxyfile.in Doxyfile @ONLY)
add_custom_command(
    OUTPUT "html/index.html"
    COMMAND "${DOXYGEN_EXECUTABLE}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    MAIN_DEPENDENCY Doxyfile
    COMMENT "Generating Doxygen documentation"
    VERBATIM
)

add_custom_target(generate_docs ALL SOURCES "html/index.html")
set_target_properties(
    generate_docs 
    PROPERTIES 
    FOLDER "${NOX_FOLDER_NAME}/docs"
)

# -------------------------------------------------------------
# Install documentation
# -------------------------------------------------------------
if(NOX_INSTALL)
    install(
        DIRECTORY "${PROJECT_SOURCE_DIR}/docs/html"
        DESTINATION "${CMAKE_INSTALL_DOCDIR}"
    )
endif()
