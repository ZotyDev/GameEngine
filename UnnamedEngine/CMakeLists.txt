# Setup the project
project(${ENGINE_NAME} VERSION ${UNNAMED_PROJECT_VERSION})

# Collect files
file(
    GLOB_RECURSE ENGINE_SOURCES
    "src/Source/*.cpp"
    "src/Source/*.hpp"
)

# Create the executable
add_library(
    ${ENGINE_NAME}
    STATIC
    ${ENGINE_SOURCES}
)

# Setup the output dir
set_target_properties(
    ${ENGINE_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${UNNAMED_BINARY_OUTPUT_DIRECTORY}/${ENGINE_NAME}
)

# Setup include directories
target_include_directories(
    ${ENGINE_NAME}
    PRIVATE
    "src/Source/"
    ${ENGINE_VENDOR_DIR}/spdlog/include
    "D:/Projects/emsdk/upstream/emscripten/system/include"
)

target_precompile_headers(
    ${ENGINE_NAME}
    PRIVATE
    "src/Source/uepch.hpp"
)