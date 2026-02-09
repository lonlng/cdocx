# Test 06: Create Empty Document Tests
# Tests for empty document creation functionality
include(CDocxHelpers)
add_cdocx_test(06_create_empty_tests 06_create_empty_tests.cpp
    LABELS "core;create"
    TIMEOUT 30)
