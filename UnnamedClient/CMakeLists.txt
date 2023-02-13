# Setup the project
project(${CLIENT_NAME} VERSION ${PROJECT_VERSION})

# Collect files
file(
    GLOB_RECURSE CLIENT_SOURCES
    "src/*.cpp"
    "src/*.hpp"
)

# Platform source files
if(MSVC)
    file(
        GLOB_RECURSE CLIENT_SOURCES_PLATFORM
        "src/Platform/Windows/*.cpp"
    )
elseif(EMSCRIPTEN)
    file(
        GLOB_RECURSE CLIENT_SOURCES_PLATFORM
        "src/Platform/Web/*.cpp"
    )
endif()

# Create the executable
add_executable(
    ${CLIENT_NAME}
    ${CLIENT_SOURCES}
    ${CLIENT_SOURCES_PLATFORM}
)

if (EMSCRIPTEN)
    target_link_options(
        ${CLIENT_NAME}
        PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/${CLIENT_NAME}/src/Platform/Web/Template.html
    )
endif()

# Setup the output dir
set_target_properties(
    ${CLIENT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${BINARY_OUTPUT_DIRECTORY}/${CLIENT_NAME}
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
    ${VENDOR_DIR}/spdlog/include
)