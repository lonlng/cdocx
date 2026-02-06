# Test 07: Text Formatting Tests
# Tests for Run and Paragraph formatting methods

cmake_minimum_required(VERSION 3.10)

# Include doctest header
include_directories(${CMAKE_SOURCE_DIR}/test)

# Copy data directory to build directory
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)

# Text formatting tests
add_cdocx_test(07_text_formatting_tests
    07_text_formatting_tests.cpp
    ${CMAKE_CURRENT_BINARY_DIR}
    LABELS "core;formatting"
    TIMEOUT 30
)
