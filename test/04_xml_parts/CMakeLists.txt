# Test 04: XML Parts API Tests
# XML Parts access, core properties, content types

cmake_minimum_required(VERSION 3.10)

# Include doctest header
include_directories(${CMAKE_SOURCE_DIR}/test)

# Copy test data to build directory
set(TEST_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
file(MAKE_DIRECTORY ${TEST_DATA_DIR})

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/data/template_test.docx
    ${TEST_DATA_DIR}/template_test.docx
    COPYONLY
)

# XML Parts tests
add_cdocx_test(04_xml_parts_tests 04_xml_parts_tests.cpp ${TEST_DATA_DIR}
    DATA_FILES template_test.docx
    LABELS "advanced;xml_parts;parts"
    TIMEOUT 30
)
