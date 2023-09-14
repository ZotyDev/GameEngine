# Setup the project
project(${TEST_NAME} VERSION ${PROJECT_VERSION})

# Collect files
file(
    GLOB TEST_SOURCES
    "src/Core/*.cpp"
)

# Create the executable
add_executable(
    ${TEST_NAME}
    ${TEST_SOURCES}
)

# Setup the output dir
set_target_properties(
    ${TEST_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${BINARY_OUTPUT_DIRECTORY}/${TEST_NAME}
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/vendor/googletest
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(
    ${TEST_NAME}
    GTest::gtest_main
    ${ENGINE_NAME}
)

include(GoogleTest)
if(WIN32)
    gtest_discover_tests(${TEST_NAME})
elseif(EMSCRIPTEN)
    target_link_options(
        ${TEST_NAME}
        PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/${TEST_NAME}/src/Platform/Web/Template.html
        PRIVATE --emrun
        PRIVATE --preload-file ${CMAKE_SOURCE_DIR}/${TEST_NAME}/env@env
    )
endif()

# Setup include directories
target_include_directories(
    ${TEST_NAME}
    PRIVATE
    ${ENGINE_LOCATION}/src/Source
    ${VENDOR_DIR}/spdlog/include
)

add_custom_command(
    TARGET ${TEST_NAME}
    PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm
    -R -f $<TARGET_FILE_DIR:${TEST_NAME}>/Assets $<TARGET_FILE_DIR:${TEST_NAME}>/Internal
)

add_custom_command(
    TARGET ${TEST_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/${TEST_NAME}/env $<TARGET_FILE_DIR:${TEST_NAME}>
)
