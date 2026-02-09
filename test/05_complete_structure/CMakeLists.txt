# Test 05: Complete Structure Tests
# Full DOCX structure loading, saving, and media management
include(CDocxHelpers)
add_cdocx_test(05_complete_structure_tests 05_complete_structure_test.cpp
    DATA complex.docx
    LABELS "advanced;structure"
    TIMEOUT 45)
