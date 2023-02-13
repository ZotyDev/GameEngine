# Setup the project
project(${TEST_NAME} VERSION ${PROJECT_VERSION})

# Collect files
file(
    GLOB TEST_SOURCES
    "Core/*.cpp"
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
if(MSVC)
    gtest_discover_tests(${TEST_NAME})
elseif(EMSCRIPTEN)
    target_link_options(
        ${TEST_NAME}
        PRIVATE --shell-file ${CMAKE_SOURCE_DIR}/${TEST_NAME}/Platform/Web/Template.html
        PRIVATE --emrun
    )
endif()

# Setup include directories
target_include_directories(
    ${TEST_NAME}
    PRIVATE
    ${ENGINE_LOCATION}/src/Source
    ${VENDOR_DIR}/spdlog/include
)