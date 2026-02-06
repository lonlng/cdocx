# Test 02: Iterator Tests
# C++11 range-based for loop and iterator functionality

cmake_minimum_required(VERSION 3.10)

# Include doctest header
include_directories(${CMAKE_SOURCE_DIR}/test)

# Copy test data to build directory
set(TEST_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
file(MAKE_DIRECTORY ${TEST_DATA_DIR})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/data/my_test.docx
    ${TEST_DATA_DIR}/my_test.docx
    COPYONLY
)

# Iterator tests
add_cdocx_test(02_iterator_tests 02_iterator_tests.cpp ${TEST_DATA_DIR}
    DATA_FILES my_test.docx
    LABELS "core;iterator;cpp11"
    TIMEOUT 30
)
