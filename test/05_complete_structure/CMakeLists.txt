# Test 05: Complete Structure Tests
# Full DOCX structure loading, saving, and media management

cmake_minimum_required(VERSION 3.10)

# Include doctest header
include_directories(${CMAKE_SOURCE_DIR}/test)

# Copy test data to build directory
set(TEST_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
file(MAKE_DIRECTORY ${TEST_DATA_DIR})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/data/template.docx
    ${TEST_DATA_DIR}/template.docx
    COPYONLY
)

# Complete structure tests
add_cdocx_test(05_complete_structure_tests 05_complete_structure_test.cpp ${TEST_DATA_DIR}
    DATA_FILES template.docx
    LABELS "advanced;complete_structure"
    TIMEOUT 60
)
