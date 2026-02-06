# Example 02: Basic Document Creation
# This example creates a new document from scratch, no input files needed

cmake_minimum_required(VERSION 3.10)

add_cdocx_executable(02_basic_create
    SOURCES main.cpp
)

# Copy empty data directory (for consistency)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")
