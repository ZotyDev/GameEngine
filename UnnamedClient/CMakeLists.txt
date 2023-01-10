# Setup the project
project(${CLIENT_NAME} VERSION ${UNNAMED_PROJECT_VERSION})

# Collect files
file(
    GLOB_RECURSE CLIENT_SOURCES
    "src/*.cpp"
    "src/*.hpp"
)

# Create the executable
add_executable(
    ${CLIENT_NAME}
    ${CLIENT_SOURCES}
)

# Setup the output dir
set_target_properties(
    ${CLIENT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${UNNAMED_BINARY_OUTPUT_DIRECTORY}/${CLIENT_NAME}
)

target_link_libraries(
    ${CLIENT_NAME}
    ${ENGINE_NAME}
)

# Setup include directories
target_include_directories(
    ${CLIENT_NAME}
    PRIVATE
    "src/Source/"
    ${ENGINE_LOCATION}/src/Source
    ${ENGINE_VENDOR_DIR}/spdlog/include
)

# set_target_properties(${CLIENT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CLIENT_ASSETS_DIR}")