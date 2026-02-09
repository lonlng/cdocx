# Test 01: Basic Functionality Tests
# Core document reading and basic operations
include(CDocxHelpers)
add_cdocx_test(01_basic_tests 01_basic_tests.cpp
    DATA my_test.docx
    LABELS "core;basic"
    TIMEOUT 30)
