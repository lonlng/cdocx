# CDocx Test CMakeLists.txt
# Modern CMake test configuration with proper test data management

cmake_minimum_required(VERSION 3.10)

# ============================================================================
# Test Configuration
# ============================================================================

# Enable C++17 for all tests
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing with CTest
enable_testing()

# ============================================================================
# Test Data Management
# ============================================================================

# Define test data directory
set(TEST_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/test_data)
file(MAKE_DIRECTORY ${TEST_DATA_DIR})

# List of test data files needed by tests
set(TEST_DATA_FILES
    my_test.docx
    template_test.docx
    template_missing_test.docx
    template_pattern_test.docx
    template_table_test.docx
    template_clear_test.docx
)

# Copy test data files to binary directory
foreach(data_file ${TEST_DATA_FILES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${data_file})
        configure_file(${data_file} ${TEST_DATA_DIR}/${data_file} COPYONLY)
        message(STATUS "Test data: ${data_file} -> ${TEST_DATA_DIR}/${data_file}")
    endif()
endforeach()

# ============================================================================
# Helper Functions
# ============================================================================

# Function to create a test executable
function(add_cdocx_test TEST_NAME SOURCE_FILE)
    add_executable(${TEST_NAME} ${SOURCE_FILE})
    
    target_link_libraries(${TEST_NAME} PRIVATE cdocx)
    
    # Set working directory for the test
    add_test(
        NAME ${TEST_NAME}
        COMMAND ${TEST_NAME}
        WORKING_DIRECTORY ${TEST_DATA_DIR}
    )
    
    # Make test depend on test data files
    foreach(data_file ${TEST_DATA_FILES})
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${data_file})
            set_tests_properties(${TEST_NAME} PROPERTIES
                DEPENDS ${TEST_DATA_DIR}/${data_file}
            )
        endif()
    endforeach()
    
    message(STATUS "Added test: ${TEST_NAME}")
endfunction()

# ============================================================================
# Test Executables
# ============================================================================

# Unit tests for basic document operations
add_cdocx_test(
    unit_tests
    basic_tests.cpp
)

# Iterator tests (checking backward compatibility with C++11)
add_cdocx_test(
    iterator_tests
    iterator_tests.cpp
)

# Template functionality tests
add_cdocx_test(
    template_tests
    template_tests.cpp
)

# Cross-run template functionality tests
add_cdocx_test(
    crossrun_tests
    crossrun_tests.cpp
)

# ============================================================================
# Test Properties and Labels
# ============================================================================

# Set common properties for all tests
set_tests_properties(
    unit_tests
    iterator_tests
    template_tests
    crossrun_tests
    PROPERTIES
    LABELS "cdocx;all"
    TIMEOUT 30
    SKIP_RETURN_CODE 254
)

# ============================================================================
# Test Dependencies and Ordering (optional - for parallel test execution)
# ============================================================================

# If tests have dependencies, they can be defined here
# For example:
# set_tests_properties(template_tests PROPERTIES DEPENDS unit_tests)

# ============================================================================
# Custom Test Targets
# ============================================================================

# Add custom target to run only unit tests
add_custom_target(test_unit
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -R unit_tests
    DEPENDS unit_tests
    COMMENT "Running unit tests"
)

# Add custom target to run only template tests
add_custom_target(test_template
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -R template_tests
    DEPENDS template_tests
    COMMENT "Running template tests"
)

# Add custom target to run all tests (aliased to test)
add_custom_target(check
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure
    DEPENDS unit_tests iterator_tests template_tests crossrun_tests
    COMMENT "Running all CDocx tests"
)

# ============================================================================
# Test Data Cleanup (optional)
# ============================================================================

# Add target to clean up test data
add_custom_target(clean_test_data
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${TEST_DATA_DIR}
    COMMENT "Cleaning test data in ${TEST_DATA_DIR}"
)

# ============================================================================
# Installation Rules
# ============================================================================

# Install test executables if requested
if(CDOCX_INSTALL_TESTS)
    install(TARGETS unit_tests iterator_tests template_tests
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/tests
    )
    
    # Install test data files
    install(DIRECTORY ${TEST_DATA_DIR}/
        DESTINATION ${CMAKE_INSTALL_BINDIR}/tests/test_data
        FILES_MATCHING PATTERN "*.docx"
    )
endif()

# ============================================================================
# Summary
# ============================================================================

message(STATUS "")
message(STATUS "Test configuration summary:")
message(STATUS "  - Test data directory: ${TEST_DATA_DIR}")
message(STATUS "  - Test executables: unit_tests, iterator_tests, template_tests, crossrun_tests")
message(STATUS "  - Run tests: ctest -C <config> or use 'check' target")
message(STATUS "")
