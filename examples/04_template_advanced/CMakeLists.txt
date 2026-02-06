# Example 04: Advanced Template Features

cmake_minimum_required(VERSION 3.10)

add_cdocx_executable(04_template_advanced
    SOURCES main.cpp
)

# Copy data directory to build directory
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
