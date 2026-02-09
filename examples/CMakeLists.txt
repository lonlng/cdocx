# ============================================================================
# CDocx Examples
# ============================================================================

include(CDocxHelpers)

# ----------------------------------------------------------------------------
# Sample Document Generator
# ----------------------------------------------------------------------------
add_cdocx_executable(create_sample_docs SOURCES create_sample_docs.cpp)

add_custom_target(generate_samples
    COMMAND create_sample_docs
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating sample documents for examples"
)

# ----------------------------------------------------------------------------
# Example Programs (Auto-discovered)
# ----------------------------------------------------------------------------
# Each example should be in its own subdirectory with:
#   - CMakeLists.txt (or auto-generated)
#   - main.cpp
#   - data/ directory (optional)
# ----------------------------------------------------------------------------

# Define all examples with their dependencies on samples
set(CDOCX_EXAMPLES
    01_basic_read:NEEDS_SAMPLES
    02_basic_create
    03_template_basic:NEEDS_SAMPLES
    04_template_advanced:NEEDS_SAMPLES
    05_document_insert:NEEDS_SAMPLES
    06_xml_parts:NEEDS_SAMPLES
    07_media_management:NEEDS_SAMPLES
    08_create_empty
    09_text_formatting
)

if(ENABLE_ADVANCED_FEATURES)
    list(APPEND CDOCX_EXAMPLES 10_advanced_crud:NEEDS_SAMPLES)
endif()

# Process each example
foreach(example_def ${CDOCX_EXAMPLES})
    # Parse definition (format: "name" or "name:NEEDS_SAMPLES")
    string(REPLACE ":" ";" parts ${example_def})
    list(GET parts 0 example)
    list(LENGTH parts parts_count)
    
    set(needs_samples FALSE)
    if(parts_count GREATER 1)
        list(GET parts 1 flag)
        if(flag STREQUAL "NEEDS_SAMPLES")
            set(needs_samples TRUE)
        endif()
    endif()
    
    # Check for custom CMakeLists.txt or auto-generate
    set(example_dir ${CMAKE_CURRENT_SOURCE_DIR}/${example})
    
    if(EXISTS ${example_dir}/CMakeLists.txt)
        # Use custom CMakeLists.txt
        add_subdirectory(${example})
    else()
        # Auto-generate target for simple examples
        if(EXISTS ${example_dir}/main.cpp)
            add_cdocx_example(${example} main.cpp)
        else()
            message(WARNING "Example ${example} has no main.cpp or CMakeLists.txt")
            continue()
        endif()
    endif()
    
    # Add sample dependency if needed
    if(needs_samples AND TARGET ${example})
        add_dependencies(${example} generate_samples)
    endif()
    
    list(APPEND ALL_EXAMPLE_TARGETS ${example})
endforeach()

# ----------------------------------------------------------------------------
# Convenience Targets
# ----------------------------------------------------------------------------

add_custom_target(examples
    DEPENDS ${ALL_EXAMPLE_TARGETS}
    COMMENT "Building all CDocx examples"
)

# ----------------------------------------------------------------------------
# Summary
# ----------------------------------------------------------------------------
message(STATUS "")
message(STATUS "[Examples]")
message(STATUS "----------")
foreach(example_def ${CDOCX_EXAMPLES})
    string(REPLACE ":" ";" example_name ${example_def})
    message(STATUS "  - ${example_name}")
endforeach()
message(STATUS "")
