# Test 06: Create Empty Document Tests
# Tests for empty document creation functionality

cmake_minimum_required(VERSION 3.10)

# Include doctest header
include_directories(${CMAKE_SOURCE_DIR}/test)

# Create empty document tests
add_cdocx_test(06_create_empty_tests
    06_create_empty_tests.cpp
    ${CMAKE_CURRENT_BINARY_DIR}
    LABELS "core;create_empty"
    TIMEOUT 30
)
