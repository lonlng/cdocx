# Test Utilities
# Debug and diagnostic tools

cmake_minimum_required(VERSION 3.10)

# Debug utilities (not actual tests, but useful for debugging)
add_executable(utils_debug_zip_read debug_zip_read.cpp)
target_link_libraries(utils_debug_zip_read PRIVATE cdocx::cdocx)

add_executable(utils_debug_zip_read2 debug_zip_read2.cpp)
target_link_libraries(utils_debug_zip_read2 PRIVATE cdocx::cdocx)

add_executable(utils_debug_doc_load debug_doc_load.cpp)
target_link_libraries(utils_debug_doc_load PRIVATE cdocx::cdocx)
