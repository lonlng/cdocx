# Test 08: Bookmark Replacement Tests
# Tests for bookmark replacement functionality including:
# - BookmarkFormat structure
# - ImageSize and ImageAlignment
# - CaptionGenerator
# - BookmarkReplacer
include(CDocxHelpers)
add_cdocx_test(08_bookmark_replacement_tests 08_bookmark_replacement_tests.cpp
    DATA ""
    LABELS "advanced;bookmark;replacement"
    TIMEOUT 60)
