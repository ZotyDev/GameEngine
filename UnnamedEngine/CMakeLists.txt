# Setup the project
project(${ENGINE_NAME} VERSION ${PROJECT_VERSION})

# Collect source files
file(
    GLOB_RECURSE ENGINE_SOURCES
    "src/Source/*.cpp"
    "src/Source/*.hpp"
)

# Platform source files
if(WIN32)
    file(
        GLOB_RECURSE ENGINE_SOURCES_PLATFORM
        "src/Platform/Windows/*.cpp"
        "src/Platform/Winsock/*.cpp"
    )
elseif(UNIX AND NOT APPLE)
    file(
        GLOB_RECURSE ENGINE_SOURCES_PLATFORM
        "src/Platform/Linux/*.cpp"
    )
elseif(APPLE)
    file(
        GLOB_RECURSE ENGINE_SOURCES_PLATFORM
        "src/Platform/MacOS/*.cpp"
    )
elseif(EMSCRIPTEN)
    file(
        GLOB_RECURSE ENGINE_SOURCES_PLATFORM
        "src/Platform/Web/*.cpp"
    )
endif()

# Create the executable
add_library(
    ${ENGINE_NAME}
    STATIC
    ${ENGINE_SOURCES}
    ${ENGINE_SOURCES_PLATFORM}
)

# Setup the output dir
set_target_properties(
    ${ENGINE_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${BINARY_OUTPUT_DIRECTORY}/${ENGINE_NAME}
)

# Setup include directories
target_include_directories(
    ${ENGINE_NAME}
    PRIVATE
    "src/Source/"
    "src/Platform/"
    ${LIB_SPDLOG_LOCATION}/include
    ${LIB_YAML_CPP_LOCATION}/include
)

# Set the common args
target_compile_options(
    ${ENGINE_NAME}
    PRIVATE
    ${CMAKE_CXX_FLAGS}
)

target_precompile_headers(
    ${ENGINE_NAME}
    PRIVATE
    "src/Source/uepch.hpp"
)

target_link_libraries(
    ${ENGINE_NAME}
    yaml-cpp
)

# Windows specific libraries
if(WIN32)
    target_link_libraries(
        ${ENGINE_NAME}
        Ws2_32
    )
endif()
