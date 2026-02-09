# CDocxHelpers.cmake
# Helper functions for building CDocx examples and tests
#
# This module provides convenient functions for:
#   - Setting up CDocx library dependencies
#   - Creating executables that link against CDocx
#   - Creating and registering tests with CTest
#
# Usage:
#   include(${CMAKE_SOURCE_DIR}/cmake/modules/CDocxHelpers.cmake)
#   require_cdocx()
#   add_cdocx_executable(my_app SOURCES main.cpp)
#   add_cdocx_test(my_test test.cpp ${TEST_DATA_DIR} LABELS "core")

# =============================================================================
# Require CDocx Library
# =============================================================================
#
# Sets up the necessary include directories and links the cdocx library.
# Must be called before using add_cdocx_executable().
#
# Usage:
#   require_cdocx()
#
function(require_cdocx)
    # Ensure cdocx target is available
    if(NOT TARGET cdocx)
        message(FATAL_ERROR "CDocxHelpers: 'cdocx' target not found. "
                            "Make sure to add_subdirectory(cdocx) before including this helper.")
    endif()
endfunction()

# =============================================================================
# Add CDocx Executable
# =============================================================================
#
# Creates an executable that links against the cdocx library.
# Automatically sets C++17 standard and UTF-8 encoding.
#
# Usage:
#   add_cdocx_executable(target_name
#       SOURCES source1.cpp source2.cpp ...
#       [WORKING_DIR dir]      # Working directory for the executable
#       [IS_SAMPLE]            # Mark as sample generator
#   )
#
function(add_cdocx_executable target_name)
    # Parse arguments
    cmake_parse_arguments(ARG
        "IS_SAMPLE"           # Options (boolean)
        "WORKING_DIR"         # Single value arguments
        "SOURCES"             # Multi value arguments
        ${ARGN}
    )

    # Validate required arguments
    if(NOT ARG_SOURCES)
        message(FATAL_ERROR "add_cdocx_executable: SOURCES argument is required")
    endif()

    # Create the executable
    add_executable(${target_name} ${ARG_SOURCES})

    # Set C++ standard
    set_target_properties(${target_name} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    # Link against cdocx library
    target_link_libraries(${target_name} PRIVATE cdocx)

    # Set include directories
    target_include_directories(${target_name} PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/thirdparty/pugixml/src
        ${CMAKE_SOURCE_DIR}/thirdparty/zip/src
    )

    # UTF-8 encoding
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /utf-8)
    else()
        target_compile_options(${target_name} PRIVATE
            -finput-charset=utf-8
            -fexec-charset=utf-8
        )
    endif()

    # Set working directory if specified
    if(ARG_WORKING_DIR)
        set_target_properties(${target_name} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${ARG_WORKING_DIR}"
        )
    endif()

    # Set output directory to be alongside the main library for easier debugging
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin
    )
endfunction()

# =============================================================================
# Add CDocx Test
# =============================================================================
#
# Creates a test executable and registers it with CTest.
#
# Usage:
#   add_cdocx_test(test_name
#       source_file                   # Single source file
#       test_data_dir                 # Directory for test data
#       [DATA_FILES file1 file2 ...]  # Data files to copy
#       [LABELS label1 label2 ...]    # CTest labels
#       [TIMEOUT seconds]             # Test timeout
#   )
#
function(add_cdocx_test test_name source_file test_data_dir)
    # Parse additional arguments
    cmake_parse_arguments(ARG
        ""                    # Options (boolean)
        "TIMEOUT"             # Single value arguments
        "DATA_FILES;LABELS"   # Multi value arguments
        ${ARGN}
    )

    # Create the test executable using our helper
    add_cdocx_executable(${test_name} SOURCES ${source_file})

    # Register with CTest
    add_test(NAME ${test_name} COMMAND ${test_name})

    # Set test properties
    set_tests_properties(${test_name} PROPERTIES
        WORKING_DIRECTORY ${test_data_dir}
    )

    # Add labels for test categorization
    if(ARG_LABELS)
        set_tests_properties(${test_name} PROPERTIES
            LABELS "${ARG_LABELS}"
        )
    endif()

    # Set timeout if specified
    if(ARG_TIMEOUT)
        set_tests_properties(${test_name} PROPERTIES
            TIMEOUT ${ARG_TIMEOUT}
        )
    endif()
endfunction()

# =============================================================================
# Copy Data Directory
# =============================================================================
#
# Helper to copy data files to build directory for examples/tests.
#
# Usage:
#   cdocx_copy_data(source_dir)
#
function(cdocx_copy_data source_dir)
    if(EXISTS "${source_dir}")
        file(COPY "${source_dir}" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
endfunction()

# =============================================================================
# Module Info
# =============================================================================
message(STATUS "CDocxHelpers loaded - CDocx build helpers available")
