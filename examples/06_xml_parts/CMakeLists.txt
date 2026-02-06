# Example 06: XML Parts API

cmake_minimum_required(VERSION 3.10)

add_cdocx_executable(06_xml_parts
    SOURCES main.cpp
)

# Copy data directory to build directory
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
