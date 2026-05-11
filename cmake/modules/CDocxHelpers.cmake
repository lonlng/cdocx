# ============================================================================
# CDocxHelpers.cmake - CMake Helper Functions for CDocx
# ============================================================================
#
# This module provides convenient functions for building CDocx examples and tests.
# Include this module after defining the cdocx target.
#
# Usage:
#   include(CDocxHelpers)
#   add_cdocx_example(01_basic_read main.cpp)
#   add_cdocx_test(01_basic_tests 01_basic_tests.cpp DATA my_test.docx LABELS "core")
#
# Supports: Linux, Windows (MSVC/MinGW), macOS

include(CMakeParseArguments)

# ----------------------------------------------------------------------------
# Internal: Check cdocx target exists
# ----------------------------------------------------------------------------
function(_require_cdocx)
    if(NOT TARGET cdocx)
        message(FATAL_ERROR "CDocxHelpers: 'cdocx' target not found. "
            "Make sure to define the cdocx target before including this helper.")
    endif()
endfunction()

# ----------------------------------------------------------------------------
# Function: add_cdocx_executable
# ----------------------------------------------------------------------------
# Creates an executable that links against cdocx with common settings.
#
# Usage:
#   add_cdocx_executable(target_name
#       SOURCES source1.cpp [source2.cpp ...]
#       [WORKING_DIR dir]      # Working directory (default: CMAKE_CURRENT_BINARY_DIR)
#   )
# ----------------------------------------------------------------------------
function(add_cdocx_executable target_name)
    cmake_parse_arguments(ARG "" "WORKING_DIR" "SOURCES" ${ARGN})
    
    if(NOT ARG_SOURCES)
        message(FATAL_ERROR "add_cdocx_executable: SOURCES argument is required")
    endif()

    add_executable(${target_name} ${ARG_SOURCES})
    
    set_target_properties(${target_name} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
    )

    target_link_libraries(${target_name} PRIVATE cdocx)
    
    # Windows-specific settings
    if(WIN32)
        target_compile_definitions(${target_name} PRIVATE
            NOMINMAX
            WIN32_LEAN_AND_MEAN
            _CRT_SECURE_NO_WARNINGS
        )
        # Windows may need specific runtime library settings
        if(MSVC)
            set_property(TARGET ${target_name} PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<BOOL:${BUILD_SHARED_LIBS}>:DLL>")
        endif()
    endif()

    if(MSVC)
        target_compile_options(${target_name} PRIVATE /utf-8)
    endif()

    # Set VS debugger working directory
    if(ARG_WORKING_DIR)
        set_target_properties(${target_name} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${ARG_WORKING_DIR}")
    else()
        set_target_properties(${target_name} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
endfunction()

# ----------------------------------------------------------------------------
# Function: add_cdocx_example
# ----------------------------------------------------------------------------
# Simplified interface for adding example programs.
# Automatically copies data/ directory if it exists.
#
# Usage:
#   add_cdocx_example(target_name main.cpp)
# ----------------------------------------------------------------------------
function(add_cdocx_example target_name main_file)
    _require_cdocx()
    
    add_cdocx_executable(${target_name} SOURCES ${main_file})
    
    # Auto-copy data directory if it exists
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/data")
        file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data" 
            DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    else()
        # Create empty data directory for consistency
        file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/data")
    endif()
endfunction()

# ----------------------------------------------------------------------------
# Function: add_cdocx_test
# ----------------------------------------------------------------------------
# Creates and registers a test executable with CTest.
#
# Usage:
#   add_cdocx_test(test_name test.cpp
#       [DATA file1 [file2 ...]]      # Data files to copy
#       [LABELS label1 [label2 ...]]  # CTest labels
#       [TIMEOUT seconds]             # Test timeout
#   )
# ----------------------------------------------------------------------------
function(add_cdocx_test test_name test_file)
    cmake_parse_arguments(ARG "" "TIMEOUT" "DATA;LABELS" ${ARGN})
    
    _require_cdocx()
    
    # Create test executable
    add_cdocx_executable(${test_name} SOURCES ${test_file})
    
    # Link with Google Test
    if(TARGET GTest::gtest_main)
        target_link_libraries(${test_name} PRIVATE GTest::gtest_main)
    elseif(TARGET gtest_main)
        target_link_libraries(${test_name} PRIVATE gtest_main)
    else()
        message(WARNING "Google Test not found, test ${test_name} may not link correctly")
    endif()
    
    # Ensure data directory exists
    set(TEST_DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
    file(MAKE_DIRECTORY ${TEST_DATA_DIR})
    
    # Copy data files
    foreach(data_file ${ARG_DATA})
        set(source_path "${CMAKE_CURRENT_SOURCE_DIR}/data/${data_file}")
        if(EXISTS ${source_path})
            configure_file(${source_path} ${TEST_DATA_DIR}/${data_file} COPYONLY)
        else()
            message(WARNING "Data file not found: ${source_path}")
        endif()
    endforeach()
    
    # Register with CTest
    add_test(NAME ${test_name} COMMAND ${test_name})
    set_tests_properties(${test_name} PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    
    if(ARG_LABELS)
        set_tests_properties(${test_name} PROPERTIES LABELS "${ARG_LABELS}")
    endif()
    
    if(ARG_TIMEOUT)
        set_tests_properties(${test_name} PROPERTIES TIMEOUT ${ARG_TIMEOUT})
    endif()
    
endfunction()

# ----------------------------------------------------------------------------
# Function: cdocx_configure_samples
# ----------------------------------------------------------------------------
# Configures sample document generation dependencies.
#
# Usage:
#   cdocx_configure_samples(TARGETS target1 target2 ...)
# ----------------------------------------------------------------------------
function(cdocx_configure_samples)
    cmake_parse_arguments(ARG "" "" "TARGETS" ${ARGN})
    
    if(NOT TARGET generate_samples)
        message(FATAL_ERROR "generate_samples target not found")
    endif()
    
    foreach(target ${ARG_TARGETS})
        if(TARGET ${target})
            add_dependencies(${target} generate_samples)
        endif()
    endforeach()
endfunction()

# ============================================================================
# Module loaded
# ============================================================================
message(STATUS "CDocxHelpers.cmake loaded (Platform: ${CMAKE_SYSTEM_NAME})")
