# Setup the project
project(${CLIENT_NAME} VERSION ${UNNAMED_PROJECT_VERSION})

# Collect files
file(
    GLOB_RECURSE CLIENT_SOURCES
    "src/Source/*.cpp"
    "src/Source/*.hpp"
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