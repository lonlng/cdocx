# Example 09: Text Formatting Features
# Demonstrates font color, size, font name, and paragraph formatting

cmake_minimum_required(VERSION 3.10)

add_cdocx_executable(09_text_formatting
    SOURCES main.cpp
)

# Copy empty data directory (for consistency)
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")
