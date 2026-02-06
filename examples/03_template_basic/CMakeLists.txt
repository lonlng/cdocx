# Example 03: Basic Template Usage

cmake_minimum_required(VERSION 3.10)

add_cdocx_executable(03_template_basic
    SOURCES main.cpp
)

# Copy data directory to build directory
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
