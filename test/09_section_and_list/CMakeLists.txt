# Test 09: Section and List Features
# Section management and numbering/list functionality
include(CDocxHelpers)
add_cdocx_test(09_section_and_list_tests 09_section_and_list_tests.cpp
    LABELS "core;section;list;numbering"
    TIMEOUT 60)
