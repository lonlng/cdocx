# Example 07: Media Management

cmake_minimum_required(VERSION 3.10)

add_cdocx_executable(07_media_management
    SOURCES main.cpp
)

# Copy data directory to build directory
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
