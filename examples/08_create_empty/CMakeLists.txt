# Example 08: Create Empty Document
# Demonstrates creating a new empty DOCX document from scratch

cmake_minimum_required(VERSION 3.10)

add_cdocx_executable(08_create_empty
    SOURCES main.cpp
)

# Copy empty data directory (for consistency)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")
