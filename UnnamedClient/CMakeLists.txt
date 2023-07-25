# Setup the project
project(${CLIENT_NAME} VERSION ${PROJECT_VERSION})

# Collect files
file(
    GLOB_RECURSE CLIENT_SOURCES
    "src/*.cpp"
    "src/*.hpp"
)

# Platform source files
if(WIN32)
    file(
        GLOB_RECURSE CLIENT_SOURCES_PLATFORM
        "src/Platform/Windows/*.cpp"
        "res/**"
    )
elseif(UNIX)
    file(
        GLOB_RECURSE CLIENT_SOURCES_PLATFORM
        "src/Platform/Linux/*.cpp"
        "res/**"
    )
elseif(EMSCRIPTEN)
    file(
        GLOB_RECURSE CLIENT_SOURCES_PLATFORM
        "src/Platform/Web/*.cpp"
    )
endif()

# Icon
set(CLIENT_ICON_RESOURCE_WINDOWS ${CMAKE_SOURCE_DIR}/${CLIENT_NAME}/res/icon.rc)

# Create the executable
add_executable(
    ${CLIENT_NAME}
    ${CLIENT_SOURCES}
    ${CLIENT_SOURCES_PLATFORM}
    ${CLIENT_ICON_RESOURCE_WINDOWS}
)

if (EMSCRIPTEN)
    target_link_options(
        ${CLIENT_NAME}
        PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/${CLIENT_NAME}/src/Platform/Web/Template.html
        PRIVATE --preload-file ${CMAKE_SOURCE_DIR}/${CLIENT_NAME}/env@env
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

# Set the common args
target_compile_options(
    ${CLIENT_NAME}
    PRIVATE
    ${CMAKE_CXX_FLAGS}
)

add_custom_command(
    TARGET ${CLIENT_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm
    -R -f $<TARGET_FILE_DIR:${CLIENT_NAME}>/Assets $<TARGET_FILE_DIR:${CLIENT_NAME}>/Internal
)

add_custom_command(
    TARGET ${CLIENT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/${CLIENT_NAME}/env $<TARGET_FILE_DIR:${CLIENT_NAME}>
)