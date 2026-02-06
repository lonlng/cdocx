# CDocx Test CMakeLists.txt
# Modern CMake test configuration with categorized test suites

cmake_minimum_required(VERSION 3.10)

# ============================================================================
# UTF-8 Encoding (important for international characters)
# ============================================================================

if(MSVC)
    add_compile_options(/utf-8)
else()
    add_compile_options(-finput-charset=utf-8 -fexec-charset=utf-8)
endif()

# ============================================================================
# Include Helper Functions
# ============================================================================

include(${CMAKE_SOURCE_DIR}/cmake/modules/CDocxHelpers.cmake)
require_cdocx()

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
# Test Suite Categories
# Each test category is in its own subdirectory with numbered prefix
# ============================================================================

set(TEST_CATEGORIES
    01_basic
    02_iterator
    03_template
    04_xml_parts
    05_complete_structure
    06_create_empty
    07_text_formatting
    utils
)

message(STATUS "")
message(STATUS "[CDocx Test Suites]")

foreach(category ${TEST_CATEGORIES})
    add_subdirectory(${category})
endforeach()

# ============================================================================
# Custom Test Targets - For Running Specific Test Categories
# ============================================================================

# Run all core tests (01 + 02)
add_custom_target(test_core
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "core" --output-on-failure
    COMMENT "Running core functionality tests (01_basic, 02_iterator)"
)

# Run all template tests
add_custom_target(test_template
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "template" --output-on-failure
    COMMENT "Running template system tests (03_template)"
)

# Run all advanced feature tests
add_custom_target(test_advanced
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "advanced" --output-on-failure
    COMMENT "Running advanced features tests (03_template, 04_xml_parts, 05_complete_structure)"
)

# Run quick smoke tests (fast tests only)
add_custom_target(test_quick
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "core" --output-on-failure
    COMMENT "Running quick smoke tests (01_basic, 02_iterator)"
)

# Run all tests with parallel execution
add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure --parallel 4
    COMMENT "Running all CDocx tests (parallel)"
)

# Alias: 'check' is the traditional Unix name for running tests
add_custom_target(check)
add_dependencies(check test_all)

# ============================================================================
# Test Coverage and Analysis
# ============================================================================

if(ENABLE_COVERAGE)
    find_program(LCOV lcov)
    find_program(GENHTML genhtml)
    
    if(LCOV AND GENHTML)
        # Add coverage flags
        target_compile_options(cdocx PUBLIC
            $<$<CONFIG:Debug>:--coverage>
            $<$<CONFIG:Debug>:-fprofile-arcs>
            $<$<CONFIG:Debug>:-ftest-coverage>
        )
        
        target_link_options(cdocx PUBLIC
            $<$<CONFIG:Debug>:--coverage>
        )
        
        # Coverage targets
        add_custom_target(coverage
            COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info
            COMMAND ${LCOV} --remove coverage.info 
                '/usr/*' 
                '*/thirdparty/*' 
                '*/test/*' 
                --output-file coverage_filtered.info
            COMMAND ${GENHTML} coverage_filtered.info --output-directory coverage_html
            COMMENT "Generating test coverage report"
        )
        
        add_custom_target(coverage_view
            COMMAND ${CMAKE_COMMAND} -E echo "Opening coverage report..."
            COMMAND ${CMAKE_COMMAND} -E start.html coverage_html/index.html
            DEPENDS coverage
            COMMENT "Opening coverage report in browser"
        )
    endif()
endif()

# ============================================================================
# Test Summary
# ============================================================================

message(STATUS "")
message(STATUS "╔════════════════════════════════════════════════════════════╗")
message(STATUS "║               CDocx Test Suite Configuration               ║")
message(STATUS "╚════════════════════════════════════════════════════════════╝")
message(STATUS "")
message(STATUS "Test Categories:")
message(STATUS "  01_basic              - Basic document reading and operations")
message(STATUS "  02_iterator           - C++11 iterator and range-based for")
message(STATUS "  03_template           - Template placeholder and insertion")
message(STATUS "  04_xml_parts          - XML Parts API")
message(STATUS "  05_complete_structure - Full DOCX structure handling")
message(STATUS "  06_create_empty       - Empty document creation")
message(STATUS "  07_text_formatting    - Text and paragraph formatting")
message(STATUS "  utils                 - Debug and diagnostic tools")
message(STATUS "")
message(STATUS "Run Commands:")
message(STATUS "  cmake --build . --target test_all    - Run all tests")
message(STATUS "  cmake --build . --target test_quick  - Run core tests only")
message(STATUS "  cmake --build . --target test_core   - Run basic + iterator")
message(STATUS "  cmake --build . --target test_template - Run template tests")
message(STATUS "  cmake --build . --target test_advanced - Run advanced tests")
message(STATUS "  ctest -C Debug --output-on-failure   - Run via CTest directly")
message(STATUS "")
