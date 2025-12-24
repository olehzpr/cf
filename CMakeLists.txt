cmake_minimum_required(VERSION 3.15)
project(cf VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/cli.cpp
    src/ui.cpp
    src/clipboard.cpp
    src/file_collector.cpp
    src/file_ignore_list.cpp
)

# Create executable
add_executable(cf ${SOURCES})

# Set output directory
set_target_properties(cf PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Install rules
install(TARGETS cf
    RUNTIME DESTINATION bin
)
