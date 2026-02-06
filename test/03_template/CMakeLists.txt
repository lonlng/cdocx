# Test 03: Template and Insertion Tests
# Template placeholder replacement and document insertion

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
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/data/main.docx
    ${TEST_DATA_DIR}/main.docx
    COPYONLY
)

# Template and insertion tests
add_cdocx_test(03_template_tests 03_template_tests.cpp ${TEST_DATA_DIR}
    DATA_FILES 
        template.docx
        main.docx
    LABELS "advanced;template;insertion"
    TIMEOUT 45
)
