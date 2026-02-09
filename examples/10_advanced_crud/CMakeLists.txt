# 10_advanced_crud - Advanced CRUD Operations Example

cmake_minimum_required(VERSION 3.10)

include(${CMAKE_SOURCE_DIR}/cmake/modules/CDocxHelpers.cmake)

# Copy sample document needed for this example
configure_file(
    ${CMAKE_SOURCE_DIR}/TestWord.docx
    ${CMAKE_CURRENT_BINARY_DIR}/TestWord.docx
    COPYONLY
)

# Build the example
add_cdocx_executable(10_advanced_crud
    SOURCES main.cpp
)
