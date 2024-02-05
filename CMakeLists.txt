cmake_minimum_required(VERSION 3.15)

project(bitcask-cpp LANGUAGES CXX)

# Set C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -Wextra)
set(CMAKE_BUILD_TYPE Release)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
# Main executable
add_library(bitcask ${SOURCES})

target_compile_options(bitcask PUBLIC -g)
# Include directories
target_include_directories(bitcask PUBLIC headers)
add_subdirectory(test/integration)
# Optional: Add testing support
enable_testing()

