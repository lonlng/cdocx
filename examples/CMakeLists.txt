# CDocx Examples CMakeLists.txt
# Organized example programs demonstrating CDocx features
# Each example has its own subdirectory with data/ folder

cmake_minimum_required(VERSION 3.10)

# ============================================================================
# UTF-8 Encoding
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
# Sample Document Generator
# This executable creates dedicated sample documents for each example
# ============================================================================

add_cdocx_executable(create_sample_docs
    SOURCES create_sample_docs.cpp
)

# Add custom target to generate sample documents
add_custom_target(generate_samples
    COMMAND create_sample_docs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating sample documents for examples"
)

# ============================================================================
# Example Programs
# Each example is in its own subdirectory with data/ folder
# ============================================================================

set(EXAMPLES
    01_basic_read
    02_basic_create
    03_template_basic
    04_template_advanced
    05_document_insert
    06_xml_parts
    07_media_management
    08_create_empty
    09_text_formatting
)

foreach(example ${EXAMPLES})
    add_subdirectory(${example})
endforeach()

# Ensure samples are generated before examples that need them run
# Note: 02_basic_create, 08_create_empty and 09_text_formatting don't need samples
add_dependencies(01_basic_read generate_samples)
add_dependencies(03_template_basic generate_samples)
add_dependencies(04_template_advanced generate_samples)
add_dependencies(05_document_insert generate_samples)
add_dependencies(06_xml_parts generate_samples)
add_dependencies(07_media_management generate_samples)

# ============================================================================
# Convenience Targets
# ============================================================================

add_custom_target(examples
    DEPENDS ${EXAMPLES}
    COMMENT "Building all examples"
)

add_custom_target(examples_list
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "CDocx Examples:"
    COMMAND ${CMAKE_COMMAND} -E echo "==============="
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "  01_basic_read          - Basic document reading"
    COMMAND ${CMAKE_COMMAND} -E echo "  02_basic_create        - Document creation and formatting"
    COMMAND ${CMAKE_COMMAND} -E echo "  03_template_basic      - Basic template processing"
    COMMAND ${CMAKE_COMMAND} -E echo "  04_template_advanced   - Advanced template features"
    COMMAND ${CMAKE_COMMAND} -E echo "  05_document_insert     - Document insertion"
    COMMAND ${CMAKE_COMMAND} -E echo "  06_xml_parts           - XML Parts API demonstration"
    COMMAND ${CMAKE_COMMAND} -E echo "  07_media_management    - Media file management"
    COMMAND ${CMAKE_COMMAND} -E echo "  08_create_empty        - Create empty document from scratch"
    COMMAND ${CMAKE_COMMAND} -E echo "  09_text_formatting     - Text and paragraph formatting features"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMAND ${CMAKE_COMMAND} -E echo "Run: cmake --build . --target examples"
    COMMAND ${CMAKE_COMMAND} -E echo ""
    COMMENT "Listing CDocx examples"
)

# ============================================================================
# Summary
# ============================================================================

message(STATUS "")
message(STATUS "CDocx Examples:")
message(STATUS "==============")
foreach(example ${EXAMPLES})
    message(STATUS "  - ${example}")
endforeach()
message(STATUS "")
