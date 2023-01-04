cmake_minimum_required(VERSION 3.5)

# Setup the project
project(${CLIENT_NAME} VERSION ${UNNAMED_PROJECT_VERSION})

# Collect files
file(
    GLOB CLIENT_SOURCES
    "src/Source/*.cpp"
    "src/Source/*.hpp"
)

# Create the executable
add_executable(
    ${CLIENT_NAME}
    ${CLIENT_SOURCES}
)

if (EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# Setup the output dir
set_target_properties(
    ${CLIENT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${UNNAMED_BINARY_OUTPUT_DIRECTORY}/${CLIENT_NAME}
)

target_include_directories(
    ${CLIENT_NAME}
    PRIVATE
    "D:/Projects/emsdk/upstream/emscripten/system/include"
)