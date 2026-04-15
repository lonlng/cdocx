# ============================================================================
# CDocx Examples
# ============================================================================

include(CDocxHelpers)

# ----------------------------------------------------------------------------
# Example Programs (Auto-discovered)
# ----------------------------------------------------------------------------
# Each example should be in its own subdirectory with:
#   - main.cpp
#   - data/ directory (optional) - will be copied to build directory
# ----------------------------------------------------------------------------

# Define all examples
set(CDOCX_EXAMPLES
    01_basic_read
    02_basic_create
    03_template_basic
    04_template_advanced
    05_document_insert
    06_xml_parts
    07_media_management
    08_create_empty
    09_text_formatting
    10_edit_document
)

if(ENABLE_ADVANCED_FEATURES)
    list(APPEND CDOCX_EXAMPLES 10_advanced_crud)
endif()

# v0.3.0: Bookmark replacement and caption generation examples
list(APPEND CDOCX_EXAMPLES 11_bookmark_replacement)
list(APPEND CDOCX_EXAMPLES 12_caption_generation)

# v0.5.0: Section and list support examples
list(APPEND CDOCX_EXAMPLES 13_enhanced_properties)
list(APPEND CDOCX_EXAMPLES 13_section_and_list)

# v0.7.0: Table merge/split example
list(APPEND CDOCX_EXAMPLES 14_table_merge)

# v0.7.0: Document search and replace example
list(APPEND CDOCX_EXAMPLES 15_document_search)

# v0.7.0: DocumentBuilder example
list(APPEND CDOCX_EXAMPLES 16_document_builder)

# v0.7.0: StyleCollection example
list(APPEND CDOCX_EXAMPLES 17_style_collection)

# DOM sync validation
list(APPEND CDOCX_EXAMPLES test_dom_sync)

# Process each example
foreach(example ${CDOCX_EXAMPLES})
    set(example_dir ${CMAKE_CURRENT_SOURCE_DIR}/${example})
    set(example_bin_dir ${CMAKE_CURRENT_BINARY_DIR}/${example})
    
    if(NOT EXISTS ${example_dir}/main.cpp)
        message(WARNING "Example ${example} has no main.cpp")
        continue()
    endif()
    
    # Create the binary directory
    file(MAKE_DIRECTORY ${example_bin_dir})
    
    # Add the executable
    add_cdocx_executable(${example} SOURCES ${example_dir}/main.cpp)
    
    # Set output directory
    set_target_properties(${example} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${example_bin_dir}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${example_bin_dir}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${example_bin_dir}
    )
    
    # Copy data directory if it exists (at configure time)
    if(EXISTS ${example_dir}/data)
        file(COPY ${example_dir}/data DESTINATION ${example_bin_dir})
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
foreach(example ${CDOCX_EXAMPLES})
    message(STATUS "  - ${example}")
endforeach()
message(STATUS "")
