set(NOX_PLUGINS_LINUX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
    ${CMAKE_CURRENT_SOURCE_DIR}/linux_dynamic_plugin.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/linux_dynamic_plugin.h
)

target_sources(${NOX_LIB_NAME} PRIVATE ${NOX_PLUGINS_LINUX_SOURCES})
