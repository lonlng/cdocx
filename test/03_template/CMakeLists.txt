# Test 03: Template and Insertion Tests
# Template placeholder replacement and document insertion
include(CDocxHelpers)
add_cdocx_test(03_template_tests 03_template_tests.cpp
    DATA template.docx main.docx
    LABELS "advanced;template;insertion"
    TIMEOUT 45)
