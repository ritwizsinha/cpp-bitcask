cmake_minimum_required(VERSION 3.20)

project(bitcask-cpp LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Test files
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")

# Main executable
add_library(bitcask ${SOURCES})

# Test executable
add_executable(bitcask-test ${TEST_SOURCES})

# Include directories
target_include_directories(bitcask PUBLIC headers)
target_include_directories(bitcask-test PRIVATE src)

# Link libraries if needed
target_link_libraries(bitcask-test PRIVATE bitcask)

# Optional: Set the output directories for executables
set_target_properties(bitcask-test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Optional: Add testing support
enable_testing()

# Add tests
add_test(NAME MyCppTests COMMAND MyCppTests)
