# Test 04: XML Parts API Tests
# XML Parts access, core properties, content types
include(CDocxHelpers)
add_cdocx_test(04_xml_parts_tests 04_xml_parts_tests.cpp
    DATA my_test.docx
    LABELS "advanced;xml;parts"
    TIMEOUT 30)
