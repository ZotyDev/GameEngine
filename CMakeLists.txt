cmake_minimum_required(VERSION 3.5)

# Setup globals
set(UNNAMED_PROJECT_VERSION 0.0.1)
set(UNNAMED_BINARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${UNNAMED_BINARY_OUTPUT_DIRECTORY})
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${UNNAMED_BINARY_OUTPUT_DIRECTORY})

set(ENVIRONMENT_NAME UnnamedEngineEnv)
set(ENGINE_NAME UnnamedEngine)
set(SERVER_NAME UnnamedServer)
set(CLIENT_NAME UnnamedClient)
set(EDITOR_NAME UnnamedEditor)
set(TEST_NAME Test)

# Setup the environment
project(${ENVIRONMENT_NAME} VERSION ${UNNAMED_PROJECT_VERSION})

# C++ variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Includes the projects
#add_subdirectory(${ENGINE_NAME})
#add_subdirectory(${SERVER_NAME})
#add_subdirectory(${CLIENT_NAME})
#add_subdirectory(${EDITOR_NAME})
add_subdirectory(${TEST_NAME})