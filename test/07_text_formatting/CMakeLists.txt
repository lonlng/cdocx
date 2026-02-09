# Test 07: Text Formatting Tests
# Tests for Run and Paragraph formatting methods
include(CDocxHelpers)
add_cdocx_test(07_text_formatting_tests 07_text_formatting_tests.cpp
    DATA formatted.docx
    LABELS "formatting;styles"
    TIMEOUT 30)
