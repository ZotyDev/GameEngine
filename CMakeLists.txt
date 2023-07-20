cmake_minimum_required(VERSION 3.5)

# Setup globals
set(PROJECT_VERSION 0.0.1)
set(VENDOR_DIR ${CMAKE_SOURCE_DIR}/vendor)

set(ENVIRONMENT_NAME UnnamedEngineEnv)
set(ENGINE_NAME UnnamedEngine)
set(SERVER_NAME UnnamedServer)
set(CLIENT_NAME UnnamedClient)
set(EDITOR_NAME UnnamedEditor)
set(TEST_NAME Test)

set(ENGINE_LOCATION ${CMAKE_SOURCE_DIR}/${ENGINE_NAME})

set(LIB_SPDLOG_LOCATION ${VENDOR_DIR}/spdlog)
set(LIB_YAML_CPP_LOCATION ${VENDOR_DIR}/yaml-cpp)

set(EMSCRIPTEN_LOCATION C:/emsdk/upstream/emscripten/system/include) 

# Setup the environment
project(${ENVIRONMENT_NAME} VERSION ${PROJECT_VERSION})

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source build detected!")
endif()

# C++ variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if((DEFINED CMAKE_BUILD_TYPE) AND (NOT CMAKE_BUILD_TYPE STREQUAL ""))
    message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_definitions(UE_DEBUG)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Develop")
        add_compile_definitions(UE_DEVELOP)
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_definitions(UE_RELEASE)
    endif()
else()
    message("CMAKE_BUILD_TYPE is unset/empty")
endif()

if(WIN32)
    set(BINARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/Windows)
elseif(EMSCRIPTEN)
    set(BINARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/Web)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    # add_compile_options(-s -static-libgcc -static-libstdc++)
elseif(UNIX)
    set(BINARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/Linux)
endif()

if(CMAKE_TESTING STREQUAL "on")
    add_compile_definitions(UE_TESTING)
endif()

# Policies
cmake_policy(SET CMP0135 NEW)

# Includes other projects
add_subdirectory(${LIB_YAML_CPP_LOCATION})

# Includes engine projects
add_subdirectory(${ENGINE_NAME})

if(CMAKE_TESTING STREQUAL "on")
    add_subdirectory(${TEST_NAME})
else()
    #add_subdirectory(${SERVER_NAME})
    add_subdirectory(${CLIENT_NAME})
    #add_subdirectory(${EDITOR_NAME})
endif()