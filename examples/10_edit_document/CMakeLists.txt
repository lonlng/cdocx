# Example 10: Edit Document with Images
# Demonstrates opening, editing text, and saving while preserving images

add_cdocx_example(10_edit_document main.cpp)

# Copy data directory to build directory
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/data)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endif()
