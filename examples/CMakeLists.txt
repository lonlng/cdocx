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
    list(APPEND CDOCX_EXAMPLES 11_advanced_crud)
endif()

# v0.3.0: Bookmark replacement and caption generation examples
list(APPEND CDOCX_EXAMPLES 12_bookmark_replacement)
list(APPEND CDOCX_EXAMPLES 13_caption_generation)

# v0.5.0: Section and list support examples
list(APPEND CDOCX_EXAMPLES 14_enhanced_properties)
list(APPEND CDOCX_EXAMPLES 15_section_and_list)

# v0.7.0: Table merge/split example
list(APPEND CDOCX_EXAMPLES 16_table_merge)

# v0.7.0: Document search and replace example
list(APPEND CDOCX_EXAMPLES 17_document_search)

# v0.7.0: DocumentBuilder example
list(APPEND CDOCX_EXAMPLES 18_document_builder)

# v0.7.0: StyleCollection example
list(APPEND CDOCX_EXAMPLES 19_style_collection)

# v0.7.0: New features alignment example
list(APPEND CDOCX_EXAMPLES 20_new_features)

# v0.8.0: MailMerge example
list(APPEND CDOCX_EXAMPLES 21_mail_merge)

# v0.8.0: TemplateEngine unified API example
list(APPEND CDOCX_EXAMPLES 23_template_engine)

# v0.8.0: CommentCollection example
list(APPEND CDOCX_EXAMPLES 22_comments)

# v0.8.0: Watermark example
list(APPEND CDOCX_EXAMPLES 24_watermark)

# v0.8.0: BookmarkInserter example
list(APPEND CDOCX_EXAMPLES 25_bookmark_inserter)

# v0.8.0: FootnoteCollection / EndnoteCollection example
list(APPEND CDOCX_EXAMPLES 26_footnote_collection)

# v0.8.0: Field switches example
list(APPEND CDOCX_EXAMPLES 27_field_switches)

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

# ----------------------------------------------------------------------------
# Additional source variants within existing example directories
# ----------------------------------------------------------------------------
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/23_template_engine/main_2.cpp)
    set(example_dir ${CMAKE_CURRENT_SOURCE_DIR}/23_template_engine)
    set(example_bin_dir ${CMAKE_CURRENT_BINARY_DIR}/23_template_engine)
    add_cdocx_executable(23_template_engine_2 SOURCES ${example_dir}/main_2.cpp)
    set_target_properties(23_template_engine_2 PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${example_bin_dir}
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${example_bin_dir}
        RUNTIME_OUTPUT_DIRECTORY_RELEASE ${example_bin_dir}
    )
    if(EXISTS ${example_dir}/data)
        file(COPY ${example_dir}/data DESTINATION ${example_bin_dir})
    endif()
    list(APPEND ALL_EXAMPLE_TARGETS 23_template_engine_2)
endif()

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
