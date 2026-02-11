# ============================================================================
# CDocx Test Suite
# ============================================================================

include(CDocxHelpers)
enable_testing()

# ----------------------------------------------------------------------------
# Test Suites
# ----------------------------------------------------------------------------

# Define test suites: name, data files, labels, timeout
macro(add_test_suite name data_files labels timeout)
    set(test_dir ${CMAKE_CURRENT_SOURCE_DIR}/${name})
    
    if(EXISTS ${test_dir}/CMakeLists.txt)
        add_subdirectory(${name})
    else()
        set(test_cpp ${name}_tests.cpp)
        if(EXISTS ${test_dir}/${test_cpp})
            add_cdocx_test(${name}_tests ${test_cpp}
                DATA ${data_files}
                LABELS ${labels}
                TIMEOUT ${timeout}
            )
        else()
            message(WARNING "Test ${name} has no ${test_cpp} or CMakeLists.txt")
        endif()
    endif()
endmacro()

add_test_suite(01_basic "my_test.docx" "core;basic" 30)
add_test_suite(02_iterator "my_test.docx" "core;iterator;cpp11" 30)
add_test_suite(03_template "template.docx;main.docx" "advanced;template;insertion" 45)
add_test_suite(04_xml_parts "my_test.docx" "advanced;xml;parts" 30)
add_test_suite(05_complete_structure "complex.docx" "advanced;structure" 45)
add_test_suite(06_create_empty "" "core;create" 30)
add_test_suite(07_text_formatting "formatted.docx" "formatting;styles" 30)
add_test_suite(08_bookmark_replacement "" "advanced;bookmark;replacement" 60)

# ----------------------------------------------------------------------------
# Test Execution Targets
# ----------------------------------------------------------------------------

add_custom_target(test_all
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure --parallel 4
    COMMENT "Running all CDocx tests"
    USES_TERMINAL
)

add_custom_target(test_core
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "core" --output-on-failure
    COMMENT "Running core tests"
)

add_custom_target(test_quick
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "core" --output-on-failure
    COMMENT "Running quick smoke tests"
)

add_custom_target(test_template
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "template" --output-on-failure
    COMMENT "Running template tests"
)

add_custom_target(test_advanced
    COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -L "advanced" --output-on-failure
    COMMENT "Running advanced feature tests"
)

add_custom_target(check)
add_dependencies(check test_all)

# ----------------------------------------------------------------------------
# Coverage Support
# ----------------------------------------------------------------------------

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    find_program(LCOV lcov)
    find_program(GENHTML genhtml)
    
    if(LCOV AND GENHTML)
        add_custom_target(coverage
            COMMAND ${LCOV} --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info
            COMMAND ${LCOV} --remove coverage.info '/usr/*' '*/thirdparty/*' '*/test/*' --output-file coverage_filtered.info
            COMMAND ${GENHTML} coverage_filtered.info --output-directory coverage_html
            COMMENT "Generating coverage report"
        )
    endif()
endif()

# ----------------------------------------------------------------------------
# Summary
# ----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "[Test Suites]")
message(STATUS "-------------")
message(STATUS "  - 01_basic")
message(STATUS "  - 02_iterator")
message(STATUS "  - 03_template")
message(STATUS "  - 04_xml_parts")
message(STATUS "  - 05_complete_structure")
message(STATUS "  - 06_create_empty")
message(STATUS "  - 07_text_formatting")
message(STATUS "")
