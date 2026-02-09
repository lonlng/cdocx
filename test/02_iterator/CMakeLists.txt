# Test 02: Iterator Tests
# C++11 range-based for loop and iterator functionality
include(CDocxHelpers)
add_cdocx_test(02_iterator_tests 02_iterator_tests.cpp
    DATA my_test.docx
    LABELS "core;iterator;cpp11"
    TIMEOUT 30)
