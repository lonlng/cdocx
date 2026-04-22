/**
 * @file document_sync.cpp
 * @brief DOM-Physical sync entry points for Document class
 * @details Public orchestration methods that delegate to specialized sync modules.
 */

#include <cdocx/document.h>

namespace cdocx {

void Document::sync_dom_and_xml(bool dom_to_xml) {
    if (dom_to_xml) {
        sync_to_physical_tree();
    } else {
        sync_from_physical_tree();
    }
}

void Document::sync_to_physical_tree() {
    sync_sections_to_physical();
    sync_comments_to_physical();
    sync_footnotes_to_physical();
    sync_endnotes_to_physical();
    sync_builtin_properties_to_physical();
    sync_custom_properties_to_physical();
}

void Document::sync_from_physical_tree() {
    sync_sections_from_physical();
    sync_comments_from_physical();
    sync_footnotes_from_physical();
    sync_endnotes_from_physical();
    sync_builtin_properties_from_physical();
    sync_custom_properties_from_physical();
}

}  // namespace cdocx
